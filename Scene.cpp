/**************************************************************
 * Author:      Paul Gallegos (PGB)
 * Date:        12/05/15
 * Comments:
***************************************************************/

#include "Scene.h"
#include <QQuickWindow>
#include <QDebug>

Scene::Scene()
    : m_isInitialized(false)
    , m_needToUpdate(true)
    , m_angularSpeed(0)
{
    connect(this, SIGNAL(windowChanged(QQuickWindow*)), this, SLOT(handleWindowChanged(QQuickWindow*)));
    setAcceptedMouseButtons(Qt::AllButtons);
    m_BasicTimer.start(40, this);
}

Scene::~Scene()
{
    m_BasicTimer.stop();
}

void Scene::changeSelectedColor(QColor newSelectedColor)
{
    m_carModel.setColor(newSelectedColor);
    m_needToUpdate = true;
}

void Scene::timerEvent(QTimerEvent*)
{
    if (window() && m_isInitialized){
        // Manage all the operations to the models
        operateModels();

        if(m_needToUpdate){
            // Update the OpenGL Scene.
            window()->update();
            m_needToUpdate = false;
        }
    }
}

void Scene::mousePressEvent(QMouseEvent* event)
{
    // Save mouse press position
    m_mousePressPosition = QVector2D(event->localPos());
}

void Scene::mouseReleaseEvent(QMouseEvent* event)
{
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(event->localPos()) - m_mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    m_rotationAxis = (m_rotationAxis * m_angularSpeed + n * acc).normalized();

    // Increase angular speed
    m_angularSpeed += acc;
}

void Scene::handleWindowChanged(QQuickWindow *window)
{
    if (window) {
        connect(window, SIGNAL(beforeSynchronizing()), this, SLOT(sync()), Qt::DirectConnection);
        connect(window, SIGNAL(afterRendering()), this, SLOT(drawAllObjects()), Qt::DirectConnection);
        window->setClearBeforeRendering(false);

        // I am not sure if I do need this function right now, but I will leave in case later I need it
//        connect(window, SIGNAL(sceneGraphInvalidated()), this, SLOT(cleanup()), Qt::DirectConnection);
    }
}

void Scene::sync()
{
    if (!m_isInitialized) {
        initializeOpenGLFunctions();
        initializeModels();
        m_isInitialized = true;
    }

    m_viewPortPosition.setX(this->position().x() * window()->devicePixelRatio());
    m_viewPortPosition.setY(window()->height() - this->height() - this->position().y());
    m_viewPortPosition.setY(m_viewPortPosition.y() * window()->devicePixelRatio());
    QSize size(this->width(), this->height());
    m_viewPortSize = size * window()->devicePixelRatio();

    // Calculate aspect ratio
    qreal aspect = qreal(m_viewPortSize.width()) / qreal(m_viewPortSize.height() ? m_viewPortSize.height() : 1);
    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 1.0, zFar = 50.0, fov = 60.0;

    // Reset projection
    m_projectionMatrix.setToIdentity();
    // Set perspective projection
    m_projectionMatrix.perspective(fov, aspect, zNear, zFar);

    glClearColor(0, 0, 0, 1);
}

void Scene::initializeModels()
{
    m_carModel.loadModel(":Models/Lexus.obj");
    m_carModel.initTextures();
    m_carModel.createShaderProgram();
    m_carModel.moveZ(-20);
    m_carModel.setScale(0.25);
}

void Scene::operateModels()
{
    // Decrease angular speed (friction)
    m_angularSpeed *= 0.99;

    // Stop rotation when speed goes below threshold
    if (m_angularSpeed < 0.01) {
        m_angularSpeed = 0.0;
    } else {
        // Update rotation
        m_rotation = QQuaternion::fromAxisAndAngle(m_rotationAxis, m_angularSpeed) * m_rotation;
        m_carModel.setRotation(m_rotation);
        m_needToUpdate = true;
    }
}

void Scene::drawAllObjects()
{
    glViewport(m_viewPortPosition.x(), m_viewPortPosition.y(), m_viewPortSize.width(), m_viewPortSize.height());
    glEnable(GL_SCISSOR_TEST);
    glClearColor(0, 0, 0, 1);
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);
    // Enable back face culling
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glScissor(m_viewPortPosition.x(), m_viewPortPosition.y(), m_viewPortSize.width(), m_viewPortSize.height());
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(m_isInitialized){
        // Draw all models inside the Scene.
        m_carModel.drawGeometry(m_projectionMatrix);
    }
    glDisable(GL_SCISSOR_TEST);
}

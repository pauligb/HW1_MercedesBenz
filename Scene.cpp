/**************************************************************
 * Author:      Paul Gallegos (PGB)
 * Date:        12/05/15
 * Comments:
***************************************************************/

#include "Scene.h"
#include <QQuickWindow>

Scene::Scene()
    : m_isInitialized(false)
{
    connect(this, SIGNAL(windowChanged(QQuickWindow*)), this, SLOT(handleWindowChanged(QQuickWindow*)));
    setAcceptedMouseButtons(Qt::AllButtons);
    m_BasicTimer.start(40, this);
}

Scene::~Scene()
{
    m_BasicTimer.stop();
}

void Scene::timerEvent(QTimerEvent*)
{
    if (window() && m_isInitialized){
        // Manage all the operations to the models
        operateModels();

        // Update the OpenGL Scene.
        window()->update();
    }
}

void Scene::mousePressEvent(QMouseEvent* /*event*/)
{
}

void Scene::mouseReleaseEvent(QMouseEvent* /*event*/)
{
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
    const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;
    // Reset projection
    m_projectionMatrix.setToIdentity();
    // Set perspective projection
    m_projectionMatrix.perspective(fov, aspect, zNear, zFar);

    glClearColor(0, 0, 0, 1);
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);
    // Enable back face culling
    glEnable(GL_CULL_FACE);
}

void Scene::initializeModels()
{
    m_carModel.initGeometry();
    m_carModel.initTextures();
    m_carModel.createShaderProgram();
    m_carModel.moveZ(-5.0);
    m_carModel.rotateX(20);
    m_carModel.rotateY(45);
}

void Scene::operateModels()
{
    m_carModel.rotateY(1);
}

void Scene::drawAllObjects()
{
    glViewport(m_viewPortPosition.x(), m_viewPortPosition.y(), m_viewPortSize.width(), m_viewPortSize.height());
    glEnable(GL_SCISSOR_TEST);
    glClearColor(0, 0, 0, 1);
    glScissor(m_viewPortPosition.x(), m_viewPortPosition.y(), m_viewPortSize.width(), m_viewPortSize.height());
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(m_isInitialized){
        // Draw all models inside the Scene.
        m_carModel.drawGeometry(m_projectionMatrix);
    }
    glDisable(GL_SCISSOR_TEST);
}

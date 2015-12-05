/**************************************************************
 * Author:      Paul Gallegos
 * Date:        12/05/15
 * Comments:
***************************************************************/

#include "CarModel.h"
#include <QQuickWindow>

CarModel::CarModel()
{
    connect(this, SIGNAL(windowChanged(QQuickWindow*)), this, SLOT(handleWindowChanged(QQuickWindow*)));
}

void CarModel::handleWindowChanged(QQuickWindow *window)
{
    if (window) {
        connect(window, SIGNAL(beforeSynchronizing()), this, SLOT(sync()), Qt::DirectConnection);
        connect(window, SIGNAL(beforeRendering()), this, SLOT(paint()), Qt::DirectConnection);
        // I am not sure if I do need this function right now, but I will leave in case later I need it
        //connect(window, SIGNAL(sceneGraphInvalidated()), this, SLOT(cleanup()), Qt::DirectConnection);
        window->setClearBeforeRendering(false);
    }
}

void CarModel::sync()
{
    QSize size(100,100);
    m_viewPortSize = size * window()->devicePixelRatio();
}

void CarModel::paint()
{
    createShaderProgram();

    m_shaderProgram->bind();

    m_shaderProgram->enableAttributeArray(0);

    float values[] = {
        -1, -1,
        1, -1,
        -1, 1,
        1, 1
    };
    m_shaderProgram->setAttributeArray(0, GL_FLOAT, values, 2);
    m_shaderProgram->setUniformValue("t", (float) 1);

    glViewport(30, 30, m_viewPortSize.width(), m_viewPortSize.height());

    glDisable(GL_DEPTH_TEST);

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    m_shaderProgram->disableAttributeArray(0);
    m_shaderProgram->release();
}

void CarModel::createShaderProgram()
{
    if (!m_shaderProgram) {
        // PGB TBD: This function should be initialized appart.
        initializeOpenGLFunctions();

        m_shaderProgram = new QOpenGLShaderProgram();
        m_shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":VertexShaders/Normal.vert");
        m_shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":FragmentShaders/Normal.frag");

        m_shaderProgram->bindAttributeLocation("vertices", 0);
        m_shaderProgram->link();
    }
}

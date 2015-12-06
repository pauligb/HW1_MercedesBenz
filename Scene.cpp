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
}

void Scene::handleWindowChanged(QQuickWindow *window)
{
    if (window) {
        connect(window, SIGNAL(beforeSynchronizing()), this, SLOT(sync()), Qt::DirectConnection);
        connect(window, SIGNAL(afterRendering()), this, SLOT(drawAllObjects()), Qt::DirectConnection);
        window->setClearBeforeRendering(false);

        // I am not sure if I do need this function right now, but I will leave in case later I need it
        //connect(window, SIGNAL(sceneGraphInvalidated()), this, SLOT(cleanup()), Qt::DirectConnection);
    }
}

void Scene::sync()
{
    if (!m_isInitialized) {
        initializeOpenGLFunctions();
        m_isInitialized = true;
    }

    m_viewPortPosition.setX(this->position().x() * window()->devicePixelRatio());
    m_viewPortPosition.setY(window()->height() - this->height() - this->position().y());
    m_viewPortPosition.setY(m_viewPortPosition.y() * window()->devicePixelRatio());

    QSize size(this->width(), this->height());
    m_viewPortSize = size * window()->devicePixelRatio();

    m_carModel.createShaderProgram();
    qDebug()<<"creating Shader Program";
}


void Scene::drawAllObjects()
{
   glViewport(m_viewPortPosition.x(), m_viewPortPosition.y(), m_viewPortSize.width(), m_viewPortSize.height());

   glEnable(GL_SCISSOR_TEST);
   glScissor(m_viewPortPosition.x(), m_viewPortPosition.y(), m_viewPortSize.width(), m_viewPortSize.height());

   glDisable(GL_DEPTH_TEST);
   glClearColor(0, 0, 0, 1);
   glClear(GL_COLOR_BUFFER_BIT);
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE);

   // Draw all the objects
   m_carModel.draw();

   glDisable(GL_SCISSOR_TEST);
}

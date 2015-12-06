/**************************************************************
 * Author:      Paul Gallegos (PGB)
 * Date:        12/05/15
 * Comments:
***************************************************************/

#ifndef SCENE_H
#define SCENE_H

#include "CarModel.h"
#include <QQuickItem>
#include <QOpenGLFunctions>


class Scene : public QQuickItem, public QOpenGLFunctions
{
    Q_OBJECT
public:
    Scene();

signals:

public slots:

private slots:
    void handleWindowChanged(QQuickWindow *window);
    void sync();
    void drawAllObjects();

private:
    bool m_isInitialized;
    QSize m_viewPortSize;
    QPointF m_viewPortPosition;

    CarModel m_carModel;
};

#endif // SCENE_H

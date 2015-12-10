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
#include <QBasicTimer>
#include <QColor>

class Scene : public QQuickItem, public QOpenGLFunctions
{
    Q_OBJECT
public:
    Scene();
    ~Scene();

public slots:
    void changeSelectedColor(QColor newSelectedColor);

protected:
    void timerEvent(QTimerEvent* timer);

private slots:
    void handleWindowChanged(QQuickWindow* window);
    void sync();
    void drawAllObjects();

private:
    void initializeModels();

    // Make all the needed operations for the models and prepare the OpenGL screen for the next time is been rendered.
    // This function is called just before the paint event is called.
    void operateModels();

    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);

    bool m_isInitialized;
    // This variable is added to know when update the model and when not
    // It must be set to true if the scene wants to be updated
    bool m_needToUpdate;
    QSize m_viewPortSize;
    QPointF m_viewPortPosition;
    QMatrix4x4  m_projectionMatrix;
    QBasicTimer m_BasicTimer;

    CarModel m_carModel;

    // This is only added to animate the car for now. It should be in a controller class.
    QVector2D m_mousePressPosition;
    QVector3D m_rotationAxis;
    qreal m_angularSpeed;
    QQuaternion m_rotation;
};

#endif // SCENE_H

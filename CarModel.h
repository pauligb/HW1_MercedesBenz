/**************************************************************
 * Author:      Paul Gallegos  (PGB)
 * Date:        12/05/15
 * Comments:
***************************************************************/

#ifndef CAR_MODEL_H
#define CAR_MODEL_H

#include <QQuickItem>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

class CarModel : public QQuickItem, public QOpenGLFunctions
{
    Q_OBJECT
public:
    CarModel();

signals:

public slots:

private slots:
    void handleWindowChanged(QQuickWindow *window);
    void sync();
    void paint();

private:
    // The next members are for the Scene
    QSize m_viewPortSize;
    QPointF m_viewPortPosition;
    bool m_isInitialized;

    // The next members are for the Car Model
    QOpenGLShaderProgram *m_shaderProgram;

    void createShaderProgram();

};

#endif // CAR_MODEL_H

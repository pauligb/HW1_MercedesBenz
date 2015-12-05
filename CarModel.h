/**************************************************************
 * Author:      Paul Gallegos
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
    QSize m_viewPortSize;
    QOpenGLShaderProgram *m_shaderProgram;

    void createShaderProgram();
};

#endif // CAR_MODEL_H

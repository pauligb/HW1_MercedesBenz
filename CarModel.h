/**************************************************************
 * Author:      Paul Gallegos  (PGB)
 * Date:        12/05/15
 * Comments:
***************************************************************/

#ifndef CAR_MODEL_H
#define CAR_MODEL_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

class CarModel : public QObject
{
    Q_OBJECT
public:
    CarModel();
    void createShaderProgram();

public slots:
    virtual void paint();

private:
    QOpenGLShaderProgram *m_shaderProgram;
};

#endif // CAR_MODEL_H

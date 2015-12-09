/**************************************************************
 * Author:      Paul Gallegos  (PGB)
 * Date:        12/05/15
 * Comments:
***************************************************************/

#ifndef CAR_MODEL_H
#define CAR_MODEL_H

#include "Model3DInterface.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>

class CarModel : public Model3DInterface
{
    Q_OBJECT
public:
    CarModel();
    ~CarModel();
    // PGB TODO: This function will be changed to setShaderProgram.
    virtual void createShaderProgram();

    virtual void loadModel(const QString& path);

    // The angle must be in radians.
    virtual void rotateX(double angle);
    // The angle must be in radians.
    virtual void rotateY(double angle);
    // The angle must be in radians.
    virtual void rotateZ(double angle);

    virtual void moveX(double distance);
    virtual void moveY(double distance);
    virtual void moveZ(double distance);

    virtual void initGeometry();
    virtual void initTextures();
    virtual void drawGeometry(QMatrix4x4 projectionMatrix);

private:
    QOpenGLShaderProgram *m_shaderProgram;
    QOpenGLTexture *m_texture;

    QOpenGLBuffer m_verticesBuffer;
    QOpenGLBuffer m_uiBuffer;
    QOpenGLBuffer m_normalBuffer;
    QOpenGLBuffer m_indexBuffer;
    unsigned int  m_indexSize;

    QVector3D m_rotationAxis;
    QPoint m_positionDistance;

    QMatrix4x4  m_projectionMatrix;
    QQuaternion m_rotation;

    // This function calculates the transformation Matrix before the object is drawn.
    virtual void createTransformationMatrix();
};

#endif // CAR_MODEL_H

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

    virtual void loadModel(const QString& path);

    // Set a specific color for the model
    virtual void setColor(const QColor color);

    // Set a specific rotation position
    virtual void setRotation(const QQuaternion angle);
    // The angle must be in degrees.
    virtual void rotateX(const double angle);
    // The angle must be in degrees.
    virtual void rotateY(const double angle);
    // The angle must be in degrees.
    virtual void rotateZ(const double angle);

    virtual void moveX(const double distance);
    virtual void moveY(const double distance);
    virtual void moveZ(const double distance);

    // This function creates the geometry of the model,
    // it must be called after creating OpenGL context and before drawing.
    virtual void initGeometry();

    // This function creates the geometry of the model,
    // it must be called after creating OpenGL context and before drawing.
    virtual void initTextures();

    // This function creates the geometry of the model,
    // it must be called after creating OpenGL context and before drawing.
    virtual void createShaderProgram();

    virtual void drawGeometry(const QMatrix4x4 projectionMatrix);

private:
    // The next variables are related to the CarObject, not to the CarModel.
    QColor m_carColor;

    // The next variables are related to the CarModel (only the texture Id)
    // All textures should be handled in a TexturesManager.
    QOpenGLShaderProgram *m_shaderProgram;
    QOpenGLTexture *m_texture;
    QOpenGLTexture *m_mainColorMask;

    QOpenGLBuffer m_verticesBuffer;
    QOpenGLBuffer m_uvBuffer;
    QOpenGLBuffer m_normalBuffer;
    QOpenGLBuffer m_indexBuffer;
    unsigned int  m_indexSize;

    // The next variable contains the position Distance in the space.
    QVector3D m_positionDistance;
    // The next variable contains the rotation angle in x, y and z.
    QVector3D m_rotationAngle;
    // The next variable is the rotation Quaternion.
    QQuaternion m_rotation;
    // The next variable is used localy to rotate the object (Perhaps will be removed).
    QVector3D m_rotationAxis;
};

#endif // CAR_MODEL_H

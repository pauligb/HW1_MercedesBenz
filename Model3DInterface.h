/**************************************************************
 * Author:      Paul Gallegos  (PGB)
 * Date:        12/05/15
 * Comments:
***************************************************************/

#ifndef MODEL3D_INTERFACE_H
#define MODEL3D_INTERFACE_H

#include <QColor>
#include <QObject>

class Model3DInterface : public QObject
{
    Q_OBJECT
public:
    virtual void createShaderProgram() = 0;

    virtual void loadModel(const QString& path) = 0;

    // Set a specific color for the model
    virtual void setColor(const QColor color) = 0;

    virtual void setRotation(QQuaternion angle) = 0;
    // The angle must be in radians.
    virtual void rotateX(const double angle) = 0;
    // The angle must be in radians.
    virtual void rotateY(const double angle) = 0;
    // The angle must be in radians.
    virtual void rotateZ(const double angle) = 0;

    virtual void moveX(const double distance) = 0;
    virtual void moveY(const double distance) = 0;
    virtual void moveZ(const double distance) = 0;

    virtual void initGeometry() = 0;
    virtual void initTextures() = 0;
    virtual void drawGeometry(const QMatrix4x4 projectionMatrix) = 0;
};

#endif // MODEL3D_INTERFACE_H

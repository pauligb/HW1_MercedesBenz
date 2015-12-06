/**************************************************************
 * Author:      Paul Gallegos  (PGB)
 * Date:        12/05/15
 * Comments:
***************************************************************/

#ifndef MODEL3D_INTERFACE_H
#define MODEL3D_INTERFACE_H

#include <QObject>

class Model3DInterface : public QObject
{
    Q_OBJECT
public:
    // PGB TODO: This function will be changed to setShaderProgram.
    virtual void createShaderProgram() = 0;

    virtual void loadModel(const QString& path) = 0;

    // The angle must be in radians.
    virtual void rotateX(double angle) = 0;
    // The angle must be in radians.
    virtual void rotateY(double angle) = 0;
    // The angle must be in radians.
    virtual void rotateZ(double angle) = 0;

    virtual void moveX(double distance) = 0;
    virtual void moveY(double distance) = 0;
    virtual void moveZ(double distance) = 0;

    virtual void draw() = 0;

private:
    // This function calculates the transformation Matrix before the object is drawn.
    virtual void createTransformationMatrix() = 0;
};

#endif // MODEL3D_INTERFACE_H

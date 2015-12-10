/**************************************************************
 * Author:      Paul Gallegos (PGB)
 * Date:        12/05/15
 * Comments:
***************************************************************/

#include "CarModel.h"
#include "ModelLoader.h"
#include <QVector3D>
#include <QVector2D>

CarModel::CarModel()
    : m_carColor(Qt::red)
    , m_shaderProgram(NULL)
    , m_indexBuffer(QOpenGLBuffer::IndexBuffer)
{
}

CarModel::~CarModel()
{
    m_verticesBuffer.destroy();
    m_indexBuffer.destroy();
    m_uvBuffer.destroy();
}

void CarModel::setColor(QColor color)
{
    m_carColor = color;
}

void CarModel::initGeometry()
{
    m_verticesBuffer.create();
    m_indexBuffer.create();
    m_uvBuffer.create();

    ModelLoader modelLoader;

    QVector<QVector3D> tempVertices;
    QVector<QVector2D> tempUVs;
    QVector<QVector3D> tempNormals;
    QVector<GLushort> tempIndices;
    modelLoader.loadObj(":Models/cube.obj", tempVertices, tempUVs, tempNormals);

    for(int i = 0; i< tempVertices.size();i++)
    {
        tempIndices.append(i);
    }

    // Transfer vertex data to VBO 0
    m_verticesBuffer.bind();
    qDebug()<<"tempVertices.size()"<<tempVertices.size();
    m_verticesBuffer.allocate(&tempVertices.at(0), tempVertices.size() * sizeof(QVector3D));
    qDebug()<<"m_verticesBuffer.size()"<<m_verticesBuffer.size();

    // Transfer index data to VBO 1
    m_indexBuffer.bind();
    m_indexBuffer.allocate(&tempIndices.at(0),  tempIndices.size() * sizeof(GLushort));

    // Transfer index data to VBO 2
    m_uvBuffer.bind();
    m_uvBuffer.allocate(&tempUVs.at(0), tempUVs.size() * sizeof(QVector2D));
}

void CarModel::initTextures()
{
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    // Load cube.png image

    m_texture = new QOpenGLTexture(QImage(":Textures/cubeCars.png"));

    // Set nearest filtering mode for texture minification
    m_texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    m_texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    m_texture->setWrapMode(QOpenGLTexture::Repeat);
    m_texture->bind();

    glActiveTexture(GL_TEXTURE1);
    // Load cube.png image
    m_mainColorMask = new QOpenGLTexture(QImage(":Textures/cubeCars_mask.png"));

    // Set nearest filtering mode for texture minification
    m_mainColorMask->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    m_mainColorMask->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    m_mainColorMask->setWrapMode(QOpenGLTexture::Repeat);
    m_mainColorMask->bind();
}

void CarModel::createShaderProgram()
{
    if (!m_shaderProgram) {
        m_shaderProgram = new QOpenGLShaderProgram();
        m_shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":VertexShaders/Normal.vert");
        m_shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":FragmentShaders/ChangeColor.frag");
        m_shaderProgram->link();
    }
}

void CarModel::loadModel(const QString& /*path*/)
{

}

void CarModel::rotateX(double angle)
{
    m_rotation = QQuaternion::fromAxisAndAngle(1, 0, 0, angle) * m_rotation;
}

void CarModel::rotateY(double angle)
{
    m_rotation = QQuaternion::fromAxisAndAngle(0, 1, 0, angle) * m_rotation;
}

void CarModel::rotateZ(double angle)
{
    m_rotation = QQuaternion::fromAxisAndAngle(0, 0, 1, angle) * m_rotation;
}

void CarModel::moveX(double distance)
{
    m_positionDistance.setX(m_positionDistance.x() + distance);
}

void CarModel::moveY(double distance)
{
    m_positionDistance.setY(m_positionDistance.y() + distance);
}

void CarModel::moveZ(double distance)
{
    m_positionDistance.setZ(m_positionDistance.z() + distance);
}

void CarModel::drawGeometry(QMatrix4x4  projectionMatrix)
{
    m_shaderProgram->bind();

    // Calculate model view transformation
    QMatrix4x4 matrix;
    matrix.translate(m_positionDistance);
    matrix.rotate(m_rotation);

    // Set modelview-projection matrix

    m_shaderProgram->setUniformValue("mvp_matrix", projectionMatrix * matrix);

    //Binding to texture 0
    m_texture->bind();
    m_shaderProgram->setUniformValue("texture", 0);

    //Binding to texture 1
    m_mainColorMask->bind();
    m_shaderProgram->setUniformValue("mainColorMask", 1);

    QVector4D carColorVector(m_carColor.redF(), m_carColor.greenF(), m_carColor.blueF(), 1);
    m_shaderProgram->setUniformValue("colorToPaint", carColorVector);

    // Tell OpenGL which VBOs to use
    m_verticesBuffer.bind();
    m_indexBuffer.bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = m_shaderProgram->attributeLocation("a_position");
    m_shaderProgram->enableAttributeArray(vertexLocation);
    m_shaderProgram->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(QVector3D));

    m_uvBuffer.bind();
    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int texcoordLocation = m_shaderProgram->attributeLocation("a_texcoord");
    m_shaderProgram->enableAttributeArray(texcoordLocation);
    m_shaderProgram->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(QVector2D));

    m_indexBuffer.bind();
    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLES, m_indexBuffer.size()/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
}

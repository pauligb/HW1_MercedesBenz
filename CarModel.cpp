/**************************************************************
 * Author:      Paul Gallegos (PGB)
 * Date:        12/05/15
 * Comments:
***************************************************************/

#include "CarModel.h"

CarModel::CarModel()
    : m_shaderProgram(NULL)
    , m_indexBuffer(QOpenGLBuffer::IndexBuffer)
{
}

CarModel::~CarModel()
{
    m_verticesBuffer.destroy();
    m_indexBuffer.destroy();
    m_uiBuffer.destroy();
}

void CarModel::initGeometry()
{
    m_verticesBuffer.create();
    m_indexBuffer.create();
    m_uiBuffer.create();

    // For cube we would need only 8 vertices but we have to
    // duplicate vertex for each face because texture coordinate
    // is different.
    QVector3D vertices[] = {
        // Vertex data for face 0
        QVector3D(-1.0f, -1.0f,  1.0f),// v0
        QVector3D( 1.0f, -1.0f,  1.0f),// v1
        QVector3D(-1.0f,  1.0f,  1.0f),// v2
        QVector3D( 1.0f,  1.0f,  1.0f),// v3

        // Vertex data for face 1
        QVector3D( 1.0f, -1.0f,  1.0f),// v4
        QVector3D( 1.0f, -1.0f, -1.0f),// v5
        QVector3D( 1.0f,  1.0f,  1.0f),// v6
        QVector3D( 1.0f,  1.0f, -1.0f),// v7

        // Vertex data for face 2
        QVector3D( 1.0f, -1.0f, -1.0f),// v8
        QVector3D(-1.0f, -1.0f, -1.0f),// v9
        QVector3D( 1.0f,  1.0f, -1.0f),// v10
        QVector3D(-1.0f,  1.0f, -1.0f),// v11

        // Vertex data for face 3
        QVector3D(-1.0f, -1.0f, -1.0f),// v12
        QVector3D(-1.0f, -1.0f,  1.0f),// v13
        QVector3D(-1.0f,  1.0f, -1.0f),// v14
        QVector3D(-1.0f,  1.0f,  1.0f),// v15

        // Vertex data for face 4
        QVector3D(-1.0f, -1.0f, -1.0f),// v16
        QVector3D( 1.0f, -1.0f, -1.0f),// v17
        QVector3D(-1.0f, -1.0f,  1.0f),// v18
        QVector3D( 1.0f, -1.0f,  1.0f),// v19

        // Vertex data for face 5
        QVector3D(-1.0f,  1.0f,  1.0f),// v20
        QVector3D( 1.0f,  1.0f,  1.0f),// v21
        QVector3D(-1.0f,  1.0f, -1.0f),// v22
        QVector3D( 1.0f,  1.0f, -1.0f),// v23
    };

    QVector2D uis[] = {

        QVector2D(0.0f, 0.0f),  // v0
        QVector2D(0.33f, 0.0f), // v1
        QVector2D(0.0f, 0.5f),  // v2
        QVector2D(0.33f, 0.5f), // v3


        QVector2D( 0.0f, 0.5f), // v4
        QVector2D(0.33f, 0.5f), // v5
        QVector2D(0.0f, 1.0f),  // v6
        QVector2D(0.33f, 1.0f), // v7


        QVector2D(0.66f, 0.5f), // v8
        QVector2D(1.0f, 0.5f),  // v9
        QVector2D(0.66f, 1.0f), // v10
        QVector2D(1.0f, 1.0f),  // v11


        QVector2D(0.66f, 0.0f), // v12
        QVector2D(1.0f, 0.0f),  // v13
        QVector2D(0.66f, 0.5f), // v14
        QVector2D(1.0f, 0.5f),  // v15


        QVector2D(0.33f, 0.0f), // v16
        QVector2D(0.66f, 0.0f), // v17
        QVector2D(0.33f, 0.5f), // v18
        QVector2D(0.66f, 0.5f), // v19


        QVector2D(0.33f, 0.5f), // v20
        QVector2D(0.66f, 0.5f), // v21
        QVector2D(0.33f, 1.0f), // v22
        QVector2D(0.66f, 1.0f)  // v23
    };

    // Indices for drawing cube faces using triangle strips.
    // Triangle strips can be connected by duplicating indices
    // between the strips. If connecting strips have opposite
    // vertex order then last index of the first strip and first
    // index of the second strip needs to be duplicated. If
    // connecting strips have same vertex order then only last
    // index of the first strip needs to be duplicated.
    GLushort indices[] = {
         0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
         4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
         8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
        12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
        16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
        20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
    };

    // Transfer vertex data to VBO 0
    m_verticesBuffer.bind();
    m_verticesBuffer.allocate(vertices, 24 * sizeof(QVector3D));

    // Transfer index data to VBO 1
    m_indexBuffer.bind();
    m_indexBuffer.allocate(indices, 34 * sizeof(GLushort));

    // Transfer index data to VBO 2
    m_uiBuffer.bind();
    m_uiBuffer.allocate(uis, 24 * sizeof(QVector2D));
}

void CarModel::initTextures()
{
    // Load cube.png image
    m_texture = new QOpenGLTexture(QImage(":Textures/cube.png").mirrored());

    // Set nearest filtering mode for texture minification
    m_texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    m_texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    m_texture->setWrapMode(QOpenGLTexture::Repeat);
}

void CarModel::createShaderProgram()
{
    if (!m_shaderProgram) {
        m_shaderProgram = new QOpenGLShaderProgram();
        m_shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":VertexShaders/Normal.vert");
        m_shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":FragmentShaders/Normal.frag");

        m_shaderProgram->bindAttributeLocation("vertices", 0);
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

    m_texture->bind();
    // Use texture unit 0 which contains cube.png
    int textureLocation = m_shaderProgram->uniformLocation("texture");
    m_shaderProgram->setUniformValue("texture", textureLocation);

    // Tell OpenGL which VBOs to use
    m_verticesBuffer.bind();
    m_indexBuffer.bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = m_shaderProgram->attributeLocation("a_position");
    m_shaderProgram->enableAttributeArray(vertexLocation);
    m_shaderProgram->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(QVector3D));

    m_uiBuffer.bind();
    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int texcoordLocation = m_shaderProgram->attributeLocation("a_texcoord");
    m_shaderProgram->enableAttributeArray(texcoordLocation);
    m_shaderProgram->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(QVector2D));

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLE_STRIP, m_indexBuffer.size()/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
}

/**************************************************************
 * Author:      Paul Gallegos (PGB)
 * Date:        12/05/15
 * Comments:
***************************************************************/

#include "CarModel.h"

CarModel::CarModel()
    : m_shaderProgram(NULL)
{
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

void CarModel::paint()
{
    m_shaderProgram->bind();

    m_shaderProgram->enableAttributeArray(0);

    float values[] = {
        -1, -1,
        1, -1,
        -1, 1,
        1, 1
    };
    m_shaderProgram->setAttributeArray(0, GL_FLOAT, values, 2);
    m_shaderProgram->setUniformValue("t", (float) 1);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    m_shaderProgram->disableAttributeArray(0);
    m_shaderProgram->release();
}

/**************************************************************
 * Author:      Paul Gallegos (PGB)
 * Date:        12/08/15
 * Comments:
***************************************************************/

#include "ModelLoader.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

ModelLoader::ModelLoader()
{

}

bool ModelLoader::loadObj(const QString& path,
                            QVector<QVector3D>& out_vertices,
                            QVector<QVector2D>& out_uvs,
                            QVector<QVector3D>& out_normals)
{
    qDebug()<<"Loading OBJ file: "<<path;

    QVector<unsigned int> vertexIndices, uvIndices, normalIndices;
    QVector<QVector3D> temp_vertices;
    QVector<QVector2D> temp_uvs;
    QVector<QVector3D> temp_normals;


    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"The file next file can not be opened";
        qDebug()<<path;
        return false;
    }

    QTextStream in(&file);
    QString line = in.readLine();
    float x = 0;
    float y = 0;
    float z = 0;
    while (!line.isNull()) {
        QStringList values = line.split(QRegExp("\\s+"));
        QString firstValue = values.at(0);

        if(0 == firstValue.compare("v"))
        {
            x = values.at(1).toFloat();
            y = values.at(2).toFloat();
            z = values.at(3).toFloat();
            temp_vertices.append(QVector3D(x, y, z));
        }else if(0 == firstValue.compare("vt"))
        {
            x = values.at(1).toFloat();
            y = values.at(2).toFloat();
            temp_uvs.append(QVector2D(x, y));
        }else if(0 == firstValue.compare("vn"))
        {
            x = values.at(1).toFloat();
            y = values.at(2).toFloat();
            z = values.at(3).toFloat();
            temp_normals.append(QVector3D(x, y, z));
        }else if(0 == firstValue.compare("f"))
        {
            QStringList face1 = values.at(1).split("/");
            QStringList face2 = values.at(2).split("/");
            QStringList face3 = values.at(3).split("/");

            vertexIndices.append(face1.at(0).toInt());
            vertexIndices.append(face2.at(0).toInt());
            vertexIndices.append(face3.at(0).toInt());
            uvIndices.append(face1.at(1).toInt());;
            uvIndices.append(face2.at(1).toInt());;
            uvIndices.append(face3.at(1).toInt());;
            normalIndices.append(face1.at(2).toInt());
            normalIndices.append(face2.at(2).toInt());
            normalIndices.append(face3.at(2).toInt());
        }

        line = in.readLine();
    }

    // For each vertex of each triangle
    for(int i=0; i < vertexIndices.size(); i++ ){

        // Get the indices of its attributes
        unsigned int vertexIndex = vertexIndices[i];
        unsigned int uvIndex = uvIndices[i];
        unsigned int normalIndex = normalIndices[i];

        // Get the attributes thanks to the index
        QVector3D vertex = temp_vertices[vertexIndex-1];
        QVector2D uv = temp_uvs[uvIndex-1];
        QVector3D normal = temp_normals[ normalIndex-1 ];

        // Put the attributes in buffers
        out_vertices.append(vertex);
        out_uvs.append(uv);
        out_normals.append(normal);
    }

    return true;
}

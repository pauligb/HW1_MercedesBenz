/**************************************************************
 * Author:      Paul Gallegos (PGB)
 * Date:        12/08/15
 * Comments:
***************************************************************/

#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H

#include <QString>
#include <QVector>
#include <QVector2D>
#include <QVector3D>

class ModelLoader
{
public:
    // This is created of future purpose, to handle loading different type of models.
    enum ModetType
    {
        MODEL_TYPE_OBJ,
        MODEL_TYPE_COUNT = MODEL_TYPE_OBJ
    };

    ModelLoader();

    static bool loadObj(const QString &path, QVector<QVector3D> &out_vertices, QVector<QVector2D> &out_uvs, QVector<QVector3D> &out_normals);
};

#endif // MODEL_LOADER_H

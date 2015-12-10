/**************************************************************
 * Author:      Paul Gallegos  (PGB)
 * Date:        12/05/15
 * Comments:
***************************************************************/

#include "Scene.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtGlobal>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<Scene>("OpenGLUnderQML", 1, 0, "Scene");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QList<QObject*> rootObjects = engine.rootObjects();
    Q_ASSERT(!rootObjects.isEmpty());

    Scene* openglScene = rootObjects.at(0)->findChild<Scene*>("OpenglScene");
    Q_ASSERT(openglScene);
    QObject* mainColorsPalette = rootObjects.at(0)->findChild<QObject*>("MainColorsPalette");
    Q_ASSERT(mainColorsPalette);

    Q_ASSERT(QObject::connect(mainColorsPalette, SIGNAL(sgn_selectedColorChanged(QColor)), openglScene, SLOT(changeSelectedColor(QColor))));

    return app.exec();
}

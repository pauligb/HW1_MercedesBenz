/**************************************************************
 * Author:      Paul Gallegos  (PGB)
 * Date:        12/05/15
 * Comments:
***************************************************************/

#include "CarModel.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<CarModel>("OpenGLUnderQML", 1, 0, "CarModel");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

import QtQuick 2.2
import QtQuick.Window 2.1
import OpenGLUnderQML 1.0

Window {
    visible: true
    width: 640
    height: 480
    property int colorsPaletteHeight: (width > height ) ? height / 8 : width / 8;

    Rectangle{
        anchors.fill: parent
        color: "black"
    }

    Scene{
        id: openglScene
        objectName: "OpenglScene"
        width: parent.width
        height: parent.height * 2 / 3
        anchors.centerIn: parent
    }

    ColorsPalette{
        objectName: "MainColorsPalette"
        height: colorsPaletteHeight
        width: parent.width
        anchors.top: openglScene.bottom
    }
}

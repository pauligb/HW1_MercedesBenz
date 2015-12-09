import QtQuick 2.2
import QtQuick.Window 2.1
import OpenGLUnderQML 1.0

Window {
    visible: true
    width: 640
    height: 480

    Rectangle{
        anchors.fill: parent
        color: "white"
    }

    Scene{
        x:0
        y:0
        width: parent.width
        height: parent.height

    }

    ColorsPalette{
        height: parent.width / 10
        width: parent.width
    }

    Image{
        anchors.left: parent.left
        anchors.bottom: parent.bottom

        width: parent.width / 10
        height: width
        anchors.margins: width / 6
        source: "images/btnRightArrow.png";
        mirror: true
    }

    Image{
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        width: parent.width / 10
        height: width
        anchors.margins: width / 6
        source: "images/btnRightArrow.png";
    }
}

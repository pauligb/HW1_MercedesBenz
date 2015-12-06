import QtQuick 2.2
import QtQuick.Window 2.1
import OpenGLUnderQML 1.0

Window {
    visible: true
    width: 600
    height: 600

    Rectangle{
        anchors.fill: parent
        color: "black"
    }

    Scene{
        width: parent.width
        height: width / 2
        anchors.centerIn: parent

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

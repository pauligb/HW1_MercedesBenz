import QtQuick 2.0

Item {
    property int numberOfColors: 3;
    property int coloritemHeight: height
    property int colorItemWidth: width / numberOfColors
    signal colorClicked(variant colorIndex)

    ListModel {
        id: myModel
        // The index values should be changed to Enum values.
        ListElement { colorName: "red";     colorIndex: 0 }
        ListElement { colorName: "green";   colorIndex: 1 }
        ListElement { colorName: "blue";    colorIndex: 2 }
    }

    Component {
        id: myDelegate
        Item{
            height: coloritemHeight
            width: colorItemWidth
            Rectangle {
                id: colorObj
                height: parent.height
                width: height
                anchors.centerIn: parent
                color: colorName
                radius: width / 2
            }
            MouseArea{
                anchors.fill: colorObj
                onClicked: colorClicked(colorIndex);
            }
        }
    }

    Row{
        Repeater {
            model: myModel
            delegate: myDelegate
        }
    }
}


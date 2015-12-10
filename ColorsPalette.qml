import QtQuick 2.0

Item {
    id: colorsPalette
    // The selected color functionality should be handled in a ColorsPaletteModel class
    property int selectedColor: 0 // This means red
    property int numberOfColors: 3;
    property int coloritemHeight: height
    property int colorItemWidth: width / numberOfColors
    signal sgn_selectedColorChanged(color newColor)

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
            Rectangle{
                height: parent.height
                width: height
                anchors.centerIn: parent
                radius: width / 2
                color: (index == selectedColor) ? "white" : "black";
                Rectangle {
                    id: colorObj
                    height: parent.height * 9 / 10
                    width: height
                    anchors.centerIn: parent
                    color: colorName
                    radius: width / 2
                }
                MouseArea{
                    anchors.fill: colorObj
                    onClicked: {
                        sgn_selectedColorChanged(colorObj.color);
                        selectedColor = index;
                    }
                }
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


import QtQuick 2.0

Item {
    id: colorsPalette
    // PGB TODO: The selected color functionality should be handled in a ColorsPaletteModel class
    property int selectedColor: 0 // This means red
    property int numberOfColors: 3;
    property int coloritemHeight: height
    property int colorItemWidth: width / numberOfColors
    signal sgn_selectedColorChanged(color newColor)

    ListModel {
        id: myModel
        // PGB TODO: The index values should be changed to Enum values.
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
                // PGB Note - TODO: For now it works because the color index is the same as the Repeater index. ColorsPalette class must be created.
                color: (colorIndex == selectedColor) ? "white" : "black";
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
                        // PGB TODO: Instead of the Repeater index, the ColorsPaleete colorIndex should be emitted
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


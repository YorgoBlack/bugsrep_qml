import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Controls.Styles 1.2
import QtQuick.Window 2.1
import QtQuick.Controls.Private 1.0

ComboBox
{
    activeFocusOnPress: true
    style: ComboBoxStyle {
    id: comboBox
    background: Rectangle {
        id: rectCategory
        color: "transparent"
        border.width: 1
        border.color: "white"
        radius: 15
    }
    label: Text {
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pointSize: 15
        font.family: "Segoe UI"
        color: "black"
        text: control.currentText
    }

    // drop-down customization here
    property Component __dropDownStyle: MenuStyle {
        __maxPopupHeight: 600
        __menuItemType: "comboboxitem"

        frame: Rectangle {              // background
            color: "gray"
            border.width: 1
            border.color: "black"
            radius: 15
        }
        padding.top: 12
        padding.bottom: 12

        itemDelegate.label:             // an item text
            Text
            {
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pointSize: 15
                font.family: "Segoe UI"
                color: "white"
                text: styleData.text
            }

        itemDelegate.background: Rectangle {  // selection of an item
            radius: 5
            color: styleData.selected ? "#1fcecb" : "transparent"
        }

        __scrollerStyle: ScrollViewStyle { }
    }

    property Component __popupStyle: Style {
        property int __maxPopupHeight: 400
        property int submenuOverlap: 100

        property Component menuItemPanel: Text {
            text: "NOT IMPLEMENTED"
            color: "red"
            font {
                pixelSize: 14
                bold: true
            }
        }

        property Component __scrollerStyle: null
        }
    }
}

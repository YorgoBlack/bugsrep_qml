import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import "styles"
import yorgo.com 1.0

Item {
    id: treeItem

    property variant value : styleData.value
    property variant myindex : styleData.index

    Rectangle {
        id: textField
        anchors.fill: parent
        color : styleData.index === treeView.currentIndex ? "white" : "#f2f2f2"
        Text {
            text: styleData.value ? styleData.value.text : ""
            font {
                pointSize: 14
                family: "Segoe UI"
                bold: styleData.value ? (styleData.value.typ === 2 ? true  : false) : false
                underline: styleData.value ? (styleData.value.typ === 1 ? true  : false) : false
            }
            color: styleData.index === treeView.currentIndex ? "blue" : "black"
        }


        MouseArea{
            anchors.fill: parent
            acceptedButtons: Qt.RightButton
            onClicked: {
                if( styleData.value ) {
                    var typ = styleData.value.typ
                    treeView.editForm.deviceIndex = -1
                    treeView.editForm.symptomIndex = -1
                    treeView.editForm.treeIndex = styleData.index
                    treeView.editForm.typ = typ
                    treePopupMenu.treeItemValue = styleData.Value

                    if( typ === 1 ) {
                        miEdit.text = "Изменить прибор"
                        miAdd.text = "Добавить проявление"
                        miDel.text = "Удалить прибор"
                        miAdd.visible = true;
                        treePopupMenu.popup()
                    }
                    else if( typ === 2 ) {
                        miEdit.text = "Изменить проявление"
                        miAdd.text = "Добавить причину (устранение)"
                        miDel.text = "Удалить проявление"
                        miAdd.visible = true;
                        treePopupMenu.popup()
                    }
                    else if( typ === 3 ) {
                        miEdit.text = "Изменить причину"
                        miDel.text = "Удалить причину (устранение)"
                        miAdd.visible = false;
                        treePopupMenu.popup()
                    } else if( typ === 4 ) {
                        miEdit.text = "Изменить устранение"
                        miDel.text = "Удалить причину (устранение)"
                        miAdd.visible = false;
                        treePopupMenu.popup()
                    }
                }
            }
        }
    }

    Menu {
        id: treePopupMenu
        property alias miEdit : miEdit
        property alias miAdd : miAdd
        property alias miDel : miDel
        property variant actionIndex
        property variant treeItemValue

        MenuItem {
            id: miAddDeviceType
            text: "Добавить прибор"
            onTriggered: {
                treeView.editForm.isInsert = true
                treeView.editForm.typ = 1
                treeView.editForm.titleLabel.text = text
                treeView.editForm.textValue_sec.visible = false
                treeView.editForm.titleLabel_sec.visible = false
                treeView.editForm.visible = true


            }
        }
        MenuSeparator {}
        MenuItem {
            id: miEdit
            text: "Изменить"
            onTriggered: {
                treeView.editForm.isInsert = false
                treeView.editForm.treeIndex = treeItem.myindex
                treeView.editForm.textValue.text = treeItem.value.text
                treeView.editForm.titleLabel.text = miEdit.text
                treeView.editForm.textValue_sec.visible = false
                treeView.editForm.titleLabel_sec.visible = false

                treeView.editForm.visible = true
            }
        }
        MenuSeparator {}
        MenuItem {
            id: miAdd
            text: "Добавить"
            onTriggered: {
                treeView.editForm.typ++
                treeView.editForm.isInsert = true
                if( treeView.editForm.typ === 2 ) {
                    treeView.editForm.titleLabel.text = "Введите новое проявление"
                    treeView.editForm.titleLabel_sec.visible = false
                    treeView.editForm.textValue_sec.visible = false
                }
                else {
                    treeView.editForm.titleLabel.text = "Введите новую причину"
                    treeView.editForm.titleLabel_sec.text = "Введите новое устранение"
                    treeView.editForm.titleLabel_sec.visible = true
                    treeView.editForm.textValue_sec.visible = true
                }
                treeView.editForm.visible = true
            }

        }
        MenuSeparator {}
        MenuItem {
            id: miDel
            text: "Удалить"
            onTriggered: {
                BugsTreeModel.delTreeItem(treeView.editForm.treeIndex)
            }
        }
    }


}

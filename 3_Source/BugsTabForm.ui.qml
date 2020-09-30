import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import "styles"

Item {
    property alias txtDate: txtDate
    property alias cbDevicesTypes: cbDevicesTypes
    property alias cbSymptoms: cbSymptoms
    property alias cbDefects: cbDefects
    property alias cbCorrection: cbCorrection
    property alias cbCameDepts: cbCameDepts
    property alias deviceID: deviceID
    property alias taComments : taComments
    property alias bugsTabForm: bugsTabForm
    property alias btnDevicesTypes: btnDevicesTypes
    property alias btnSymptoms: btnSymptoms
    property alias btnDefects: btnDefects
    property alias btnCameDepts : btnCameDepts
    property alias btnCameDepts_Del : btnCameDepts_Del
    property alias btnWriteToReport : btnWriteToReport

    anchors.rightMargin: 20
    anchors.leftMargin: 20
    anchors.bottomMargin: 20
    anchors.topMargin: 20
    anchors.bottom: parent.bottom
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.top: parent.top

    id: bugsTabForm

    GridLayout {
            columns: 2
            rows: 5
            columnSpacing: 30
            anchors.fill : parent

            RowLayout {
                Layout.columnSpan: 2
                Item {
                    Layout.columnSpan: 2
                    Layout.fillWidth: true
                    implicitHeight: txtDate.height

                    Label {
                        Layout.fillWidth: true
                        anchors.centerIn: parent

                        id: txtDate
                        font {
                            pointSize: 20
                        }

                        text: "Дата"
                    }
                }
            }


        ColumnLayout {
        Layout.rowSpan: 2
        GridLayout {
            id: gridLayout3
            anchors.rightMargin: 0
            anchors.bottomMargin: 0
            anchors.leftMargin: 0
            anchors.topMargin: 0
            rowSpacing: 5
            columns: 3
            rows: 11
            anchors.fill: parent

            RowLayout {
                Layout.columnSpan: 3
                Label {
                    id: labelDevicesTypes
                    text: qsTr("Выберите прибор")
                    transformOrigin: Item.Right
                }
            }
            CPXComboBox {
                Layout.fillWidth: true
                id: cbDevicesTypes
            }

            Button {
                id: btnDevicesTypes
                anchors.leftMargin: 5
                anchors.left: cbDevicesTypes.right
                text: "+"
            }
            Item {}

            RowLayout {
                Layout.columnSpan: 3
                Label {
                    text: qsTr("Выберите проявление")
                }
            }
            CPXComboBox {
                Layout.fillWidth: true
                id: cbSymptoms
            }
            Button {
                id: btnSymptoms
                anchors.leftMargin: 5
                anchors.left: cbSymptoms.right
                text: "+"
            }
            Item {}

            RowLayout {
                Layout.columnSpan: 3
                Label {
                    text: qsTr("Выберите причину")
                }
            }
            CPXComboBox {
                Layout.fillWidth: true
                id: cbDefects
            }
            Button {
                id: btnDefects
                anchors.leftMargin: 5
                anchors.left: cbDefects.right
                enabled: cbSymptoms.currentIndex > 0
                text: "+"
            }
            Item {}

            RowLayout {
                Layout.columnSpan: 3
                Label {
                    text: qsTr("Действие")
                }
            }
            CPXComboBox {
                Layout.fillWidth: true
                id: cbCorrection
            }
            Item {}
            Item {}

            RowLayout {
                Layout.columnSpan: 3
                Label {
                    text: qsTr("Выберите источник")
                }
            }
            CPXComboBox {
                Layout.fillWidth: true
                id: cbCameDepts
            }
            Button {
                id: btnCameDepts
                anchors.leftMargin: 5
                anchors.left: cbCameDepts.right
                text: "+"
            }
            Button {
                id: btnCameDepts_Del
                anchors.leftMargin: 5
                anchors.left: btnCameDepts.right
                text: "-"
            }
        }
        }

        CPXTextField {
            id: deviceID
            Layout.preferredWidth: 280
            placeholderText: focus ? "Сканируйте ID" : ""
        }

        CPXButton {
            id: btnWriteToReport
            Layout.preferredWidth: 200
            Layout.preferredHeight: 100
            text: qsTr("Готово")
            enabled: deviceID.text != ""
        }

        RowLayout {
            Layout.columnSpan: 2
            Label {
                text: qsTr("Комментарий")
            }
        }
        RowLayout {

            Layout.columnSpan: 2
            TextArea {
                id: taComments
                Layout.fillWidth: true
                Layout.preferredHeight: 100
            }
        }
    }
}






import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2


Item {
    property alias saveButton: saveButton
    property alias bugsConfigPath: bugsConfigPath
    property alias bugsRepPath: bugsRepPath
    property alias tabTitle: tabTitle
    property  alias tbSelectFileConfig: tbSelectFileConfig
    property  alias tbSelectFileReport: tbSelectFileReport

    Rectangle {
        id: tabRectangle
        y: 20
        height: tabTitle.height * 2
        color: "#46a2da"
        anchors.rightMargin: 0
        anchors.leftMargin: 0
        anchors.left: parent.left
        anchors.right: parent.right

        Label {
            id: tabTitle
            color: "#ffffff"
            text: qsTr("Настройки")
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    Item {
        id: item2
        anchors.rightMargin: 20
        anchors.leftMargin: 20
        anchors.bottomMargin: 20
        anchors.topMargin: 20
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: tabRectangle.bottom

        GridLayout {
            id: gridLayout3
            anchors.rightMargin: 0
            anchors.bottomMargin: 0
            anchors.leftMargin: 0
            anchors.topMargin: 0
            rowSpacing: 20
            rows: 2
            columns: 3
            anchors.fill: parent

            Label {
                id: label2
                text: qsTr("Файл конфигурации")
                visible: false
            }

            TextField {
                id: bugsConfigPath
                Layout.fillWidth: true
            }

            ToolButton {
                id: tbSelectFileConfig
                text: "\u2600"
                width: 2
            }

            Label {
                id: label3
                text: qsTr("Файл журнала")
            }

            TextField {
                id: bugsRepPath
                Layout.fillWidth: true
            }

            ToolButton {
                id: tbSelectFileReport
                text: "\u2600"
                width: 2
            }

            RowLayout {
                id: rowLayout1
                Layout.columnSpan: 3
                Layout.alignment: Qt.AlignLeft

                Button {
                    id: saveButton
                    text: qsTr("Применить")
                }

            }
            Item {
                Layout.fillHeight: true
                Layout.columnSpan: 2
            }
        }
    }
}

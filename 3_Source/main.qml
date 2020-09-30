import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Dialogs 1.1



ApplicationWindow {

    visible: true
    width: 1300
    height: 600
    title: qsTr("Сбор статистики")
    id: appWin

    StackView {
        id: stackView
        anchors.fill: parent

        BugsPage {
            id: bugsPage
            anchors.fill: parent
            enabled: true
            visible: tbSetting.visible
        }

        SettingsPage {
            id: settingsPage
            anchors.fill: parent
            visible: !tbSetting.visible
        }

    }

    toolBar: ToolBar {
        ToolButton {
            id: tbSetting
            text: "\u2630"
            visible: true
            onClicked: {
                visible = false
                settingsPage.bugsRepPath.text = AppSettings.bugsRepPath()
            }
        }
        ToolButton {
            text: "<<"
            visible: !tbSetting.visible
            onClicked: tbSetting.visible = true
        }

        ToolButton {
            id: tbLoadBugsConfig
            text: "Загрузить списки"
            anchors.right: tbSaveBugsConfig.left
            onClicked: {
                fileDialogLoad.open()
            }
        }

        ToolButton {
            id: tbSaveBugsConfig
            text: "Сохранить списки"
            anchors.right: parent.right
            onClicked: {
                fileDialogSave.open()
            }
        }
    }

    statusBar: StatusBar {
        RowLayout {
            anchors.fill: parent
            Label {
                id: statusBarText
                text: "Версия " + AppSettings.getVersion()
            }
        }
    }

    FileDialog {
        id: fileDialogLoad
        nameFilters: [ "Файлы конфигурации (*.xml)" ]
        onAccepted: {
            AppSettings.loadBugsFromFile(decodeURIComponent(fileUrl.toString().replace(/^(file:\/{3})/,"")))
        }
    }
    FileDialog {
        id: fileDialogSave
        nameFilters: [ "Файлы конфигурации (*.xml)" ]
        selectExisting: false
        onAccepted: {
            AppSettings.saveBugsToFile(decodeURIComponent(fileUrl.toString().replace(/^(file:\/{3})/,"")))
        }
    }



}

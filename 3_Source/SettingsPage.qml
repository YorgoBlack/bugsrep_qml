import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.1

SettingsPageForm {

    FileDialog {
        id: fdConfig
        nameFilters: [ "Файлы конфигурации (*.xml)" ]
        onAccepted: {
            bugsConfigPath.text = decodeURIComponent(fileUrl.toString().replace(/^(file:\/{3})/,""))
        }
    }
    FileDialog {
        id: fdReport
        title: "Выберите каталог для хранения файлов отчетов"
        selectFolder: true
        selectExisting: false
        onAccepted: {
            bugsRepPath.text = decodeURIComponent(fileUrl.toString().replace(/^(file:\/{3})/,""))
        }

    }

    bugsConfigPath.visible: false
    bugsConfigPath.onAccepted: {
        AppSettings.tryLoadBugsTree(bugsConfigPath.text)
    }

    tbSelectFileConfig.visible: false
    tbSelectFileConfig.onClicked: {
        fdConfig.open()
    }

    tbSelectFileReport.onClicked: {
        fdReport.open()
    }

    saveButton.onClicked: {
        AppSettings.setBugsRepPath(bugsRepPath.text)
    }

    Component.onCompleted: {
        bugsConfigPath.text = AppSettings.bugsConfigPath();
        bugsRepPath.text = AppSettings.bugsRepPath();
    }

}

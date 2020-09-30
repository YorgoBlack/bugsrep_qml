import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Controls.Styles.Flat 1.0 as Flat
import QtQuick.Extras 1.4

BugsTabForm {

        id: bugsForm

        Timer {
           interval: 2000; running: true; repeat: true
           onTriggered: {
               if( ! (popup.visible || taComments.focus || !bugsForm.visible )) {
                  deviceID.forceActiveFocus()
                   console.log("timer")
               }
           }
        }

        Component.onCompleted: {
            setupModel(true)
        }

        cbDevicesTypes.onCurrentIndexChanged: {
            cbSymptoms.model = []
            cbSymptoms.model = BugsTreeModel.getSymptoms(cbDevicesTypes.currentIndex)
        }

        cbSymptoms.onCurrentIndexChanged: {
            cbDefects.model = []
            cbCorrection.model = []
            cbDefects.model = BugsTreeModel.getDefects(cbDevicesTypes.currentIndex, cbSymptoms.currentIndex)
        }

        cbDefects.onCurrentIndexChanged: {
            cbCorrection.model = []
            cbCorrection.model = BugsTreeModel.getCorrection(cbDevicesTypes.currentIndex, cbSymptoms.currentIndex,cbDefects.currentIndex)
        }

        btnDevicesTypes.onClicked: {
            popup.titleLabel.text = qsTr("Введите новый прибор")
            popup.isInsert = true
            popup.titleLabel_sec.visible = false
            popup.textValue_sec.visible = false
            popup.textValue.text = ""
            popup.textValue_sec.text = ""
            popup.typ = 1
            popup.visible = true;
        }

        btnSymptoms.onClicked: {
            popup.isInsert = true
            popup.deviceIndex = cbDevicesTypes.currentIndex
            popup.titleLabel.text = qsTr("Введите новое проявление")
            popup.titleLabel_sec.visible = false
            popup.textValue_sec.visible = false
            popup.textValue.text = ""
            popup.textValue_sec.text = ""
            popup.typ = 2

            popup.visible = true
        }
        btnDefects.onClicked: {
            popup.isInsert = true
            popup.deviceIndex = cbDevicesTypes.currentIndex
            popup.symptomIndex = cbSymptoms.currentIndex - 1
            popup.titleLabel.text = qsTr("Введите новую причину")
            popup.titleLabel_sec.text = qsTr("Введите действие")
            popup.titleLabel_sec.visible = true
            popup.textValue_sec.visible = true
            popup.textValue.text = ""
            popup.textValue_sec.text = ""
            popup.typ = 3
            popup.visible = true;
        }
        btnCameDepts.onClicked: {
            popup.titleLabel.text = qsTr("Введите новый источник")
            popup.titleLabel_sec.visible = false
            popup.textValue_sec.visible = false
            popup.textValue.text = ""
            popup.textValue_sec.text = ""
            popup.typ = 5
            popup.visible = true;
            popup.isInsert = true
        }

        btnCameDepts_Del.onClicked: {
            BugsTreeModel.delCamedepts(cbCameDepts.currentIndex)
        }

        btnWriteToReport.onClicked: {
            AppSettings.writeToReport(deviceID.text,cbDevicesTypes.currentText,cbSymptoms.currentText,
                                      cbDefects.currentText,cbCorrection.currentText,
                                      cbCameDepts.currentText, taComments.text )
            deviceID.text = ""

        }

        Connections {
            target: BugsTreeModel
            onUpdDeviceTypes: {
                cbDevicesTypes.model = list
                cbDevicesTypes.currentIndex = cbDevicesTypes.count -1
            }
            onUpdSymptoms: {
                console.log(list)
                cbSymptoms.model = list
                cbSymptoms.currentIndex = cbSymptoms.count - 1

            }
            onUpdDefects: {
                console.log(list)
                cbDefects.model = list
                cbDefects.currentIndex = cbDefects.count - 1
            }
            onUpdCameDepts: {
                console.log(list)
                cbCameDepts.model = list
                if( cbCameDepts.count === 0 ) {
                    cbCameDepts.currentIndex = -1
                }
            }

            onDataChanged: {
                setupModel(false)
            }

        }

        Connections {
            target: AppSettings
            onAlertMsg: {
                mBox.message.text = msg
                mBox.show()
            }

        }

        Window  {
            id: mBox
            property alias  message: message
            title: qsTr("Сообщение системы !!!")
            width: 600
            height: 150
            flags: Qt.Dialog
            modality: Qt.WindowModal
            GridLayout {
                anchors.fill: parent
                anchors.margins: 10
                rows: 2
                columns: 1
                Label {
                    id: message
                    anchors.fill: parent
                    text: "Сообщение"
                    Layout.fillHeight: true
                }

                Button {
                    Layout.alignment: Qt.AlignCenter
                    text: qsTr("Закрыть")
                    height: 20
                    onClicked: {
                        mBox.close()
                    }
                }
            }
        }

        EditBugForm {
            id: popup
        }

        function setupModel(onLoad) {
            txtDate.text = "Сегодня "  + Qt.formatDateTime(new Date(), "dd.MM.yyyy")
            cbDevicesTypes.model = BugsTreeModel.getDevicesTypes()
            cbCameDepts.model = BugsTreeModel.getCamedepts()
            if( onLoad ) {
                cbSymptoms.model = []
                cbDefects.model = []
                cbCorrection.model = []
                deviceID.forceActiveFocus()
            }
            else {
                cbSymptoms.model = BugsTreeModel.getSymptoms(cbDevicesTypes.currentText)
                cbDefects.model = BugsTreeModel.getDefects(cbDevicesTypes.currentText,
                                                           cbSymptoms.currentIndex - 1)
                cbCorrection.model = BugsTreeModel.getCorrection(cbDevicesTypes.currentText,
                                                                 cbSymptoms.currentIndex - 1,
                                                                 cbDefects.currentIndex)
            }
        }

 }


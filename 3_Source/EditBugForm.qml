import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Controls.Styles.Flat 1.0 as Flat
import QtQuick.Extras 1.4

Window  {
    property alias titleLabel : titleLabel
    property alias titleLabel_sec : titleLabel_sec
    property alias textValue : textValue
    property alias textValue_sec : textValue_sec
    property int typ : 1
    property bool isInsert : true
    property variant treeIndex
    property int deviceIndex
    property int symptomIndex


    width: 800
    height: 200
    visible: false
    color: "#e6ffe6"
    title: "Сбор статистики"
    flags: Qt.Dialog
    modality: Qt.WindowModal

    GridLayout {
        anchors.fill: parent
        anchors.margins: 10
        columns: 2
        rows: 5
        RowLayout {
            Layout.fillWidth: true
            Layout.columnSpan: 2
            Label {
                id: titleLabel
            }
        }
        RowLayout {
            Layout.fillWidth: true
            Layout.columnSpan: 2
            TextField {
                id: textValue
                Layout.preferredWidth: 780
                focus: true
                Keys.onReturnPressed: {
                    saveAndClose()
                }
                Keys.onEnterPressed: {
                    saveAndClose()
                }
            }
        }
        RowLayout {
            Layout.fillWidth: true
            Layout.columnSpan: 2
            Label {
                id: titleLabel_sec
            }
        }
        RowLayout {
            Layout.fillWidth: true
            Layout.columnSpan: 2
            TextField {
                id: textValue_sec
                Layout.preferredWidth: 780
                focus: true
                Keys.onReturnPressed: {
                    saveAndClose()
                }
                Keys.onEnterPressed: {
                    saveAndClose()
                }
            }
        }


        Item {
            Layout.columnSpan: 2
            Layout.fillWidth: true
            implicitHeight: button.height

            Button {
                id: button
                anchors.centerIn: parent
                text: qsTr("Сохранить")
                onClicked: {
                    saveAndClose()
                }
            }
        }
    }

    function saveAndClose() {
        var t
        visible = false

        console.log("send save ..." + typ)

        if( typ == 1 ) {
            t = textValue.text
            if( isInsert ) {
                BugsTreeModel.addDevicesType(0,t)
            }
            else {
                BugsTreeModel.editTreeItem(treeIndex,t,typ)
            }

        }
        else if(typ == 2) {
            t = textValue.text
            if( isInsert ) {
                BugsTreeModel.addSymptom(deviceIndex, 0, t, treeIndex)
            }
            else {
                BugsTreeModel.editTreeItem(treeIndex,t,typ)
            }
        }
        else if(typ == 3 || typ == 4) {
            t = textValue.text
            if( isInsert ) {
                var t_sec = textValue_sec.text
                BugsTreeModel.addDefect(deviceIndex, symptomIndex, 0, t, t_sec, treeIndex)
            }
            else {
                BugsTreeModel.editTreeItem(treeIndex,t,typ)
            }
        }
        else if(typ == 5) {
            t = textValue.text
            BugsTreeModel.addCamedepts(cbCameDepts.count,t)
            cbCameDepts.model = BugsTreeModel.getCamedepts();
            cbCameDepts.currentIndex = cbCameDepts.count - 1;
        }
    }

}

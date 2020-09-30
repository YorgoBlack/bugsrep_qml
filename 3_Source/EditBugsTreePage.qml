import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQml.Models 2.2
import QtQuick.Layouts 1.2
import QtQuick.Controls.Styles 1.4

TreeView {

    property alias editForm : editForm

    id: treeView
    anchors.fill: parent
    model: BugsTreeModel


    itemDelegate: TreeDelegate {}

    TableViewColumn {
        id: ccDevColumn
        title: qsTr("Прибор (проявление, причина)")
        role: "device"
        resizable: true
        width: treeView.width - ccCorrectionColumn.width - 10
    }
    TableViewColumn {
        id: ccCorrectionColumn
        title: qsTr("Действие")
        role: "defect"
        resizable: true
        width: 500
    }

    rowDelegate: Rectangle {
        height: 28
        Text {
            anchors.fill: parent
        }
    }
    EditBugForm {
        id: editForm

    }

    Connections {
        target: AppSettings
        onModelSaved: {
            console.log("tree update")
        }
    }


    function expandAll() {

        for(var i=0; i < model.rowCount(); i++) {
            var index = model.index(i,0)
            if(!treeView.isExpanded(index)) {
                treeView.expand(index)
            }
            else {
                treeView.collapse(index)
            }
        }
    }

    Component.onCompleted: {
    }

}


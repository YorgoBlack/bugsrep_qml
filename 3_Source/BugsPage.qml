import QtQuick 2.5
import QtQuick.Controls 1.4


TabView {

    property variant appTreeModel


    id: tabView
    Tab {
        title: "Внесение в базу"
        anchors.fill: parent
        source: "qrc:///BugsTab.qml"
    }

    Tab {
        title: "Редактирование списков"
        enabled: true
        source: "qrc:///EditBugsTreePage.qml"

    }
    Tab {
        title: "Просмотр базы"
        enabled: false
    }
    Tab {
        title: "Статистика"
        enabled: false
    }

    onCurrentIndexChanged:  {
    }
    Component.onCompleted: {
        appTreeModel = BugsTreeModel
    }
}

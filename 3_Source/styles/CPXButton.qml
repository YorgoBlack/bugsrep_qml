import QtQuick 2.5
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Button {
    id: cmdQuit
    text: qsTr("Quit")
    width: 64
    height: 32
    style: ButtonStyle {
      label: Text {
        renderType: Text.NativeRendering
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.family: "Segoe UI"
        font.pointSize: 20
        color: control.enabled ? "blue" : "gray"
        text: control.text
      }
    }
}

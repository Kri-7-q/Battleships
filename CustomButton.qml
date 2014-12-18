import QtQuick 2.0
import QtQuick.Controls.Styles 1.1

ButtonStyle {
    id: buttonStyle
    property color color: "yellow"
    property int fontSize: 12

    background: Rectangle {
        radius: height / 2
        color: buttonStyle.color
        border.color: control.activeFocus ? "black" : "gray"
        border.width: control.activeFocus ? 2 : 1
    }
    label: Text {
        renderType: Text.NativeRendering
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: buttonStyle.fontSize
        color: "black"
        text: control.text
      }
}

import QtQuick 2.0
import QtQuick.Controls.Styles 1.1

ButtonStyle {
    id: buttonStyle
    property color color: "yellow"
    property color inactiveColor: "lightgray"
    property int fontSize: 12

    background: Rectangle {
        radius: height / 2
        color: control.enabled ? buttonStyle.color : inactiveColor
        border.color: control.activeFocus ? "gray" : "black"
        border.width: control.activeFocus ? 4 : 1
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

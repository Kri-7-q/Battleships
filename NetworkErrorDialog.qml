import QtQuick 2.0
import QtQuick.Controls 1.2

Rectangle {
    width: parent.width * 0.8
    height: parent.height * 0.8
    anchors.centerIn: parent
    color: "goldenrod"
    border.color: "gray"
    border.width: 3
    property int margin: 20
    anchors.margins: margin
    radius: 20
    scale: window.scale

    Column {
        anchors.centerIn: parent
        spacing: 20

        Text {
            font.pixelSize: 35
            text: qsTr("Network error !")
            color: "red"
        }

        Text {
            font.pixelSize: 25
            text: qsTr(controler.networkError)
        }

        Button {
            width: 100
            height: 30
            text: qsTr("OK")
            style: CustomButton {}
        }
    }
}

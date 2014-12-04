import QtQuick 2.0
import QtQuick.Controls 1.2

ApplicationWindow {
    width: 960
    height: 480
    visible: true
    title: "Battleships"

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem { text: qsTr("Close") }
        }
        Menu {
            title: qsTr("Mode")
            MenuItem { text: qsTr("Single Player") }
            MenuItem { text: qsTr("Multi Player") }
        }
    }

    // Draw background
    Rectangle {
        id: background
        property double widthFactor: width / 960
        property double heightFactor: height / 480
        anchors.fill: parent
        color: "lightblue"
    }

    SettingsDialog {
        visible: false
        anchors.centerIn: parent
    }

    Item {
        id: sizeAndNetworkDialog
        width: itemColumn.width
        height: itemColumn.height
        anchors.centerIn: parent

        Column {
            id: itemColumn
            width: background.width * 0.8
            spacing: 10

            Text {
                font.pixelSize: 24 * background.widthFactor
                text: qsTr("Please insert the size of your game board.")
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Text {
                font.pixelSize: 11 * background.widthFactor
                text: qsTr("Min. 5 x 5 and max. size 20 x 20 Fields.")
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Row {
                spacing: 10
                anchors.horizontalCenter: parent.horizontalCenter
                TextField {
                    width: 50
                    text: qsTr("width")
                }
                Rectangle {
                    width: 10
                    height: parent.height
                    color: "transparent"
                    Text {
                        text: "x"
                        anchors.centerIn: parent
                    }
                }
                TextField {
                    width: 50
                    text: qsTr("height")
                }
            }
        }
    }
}

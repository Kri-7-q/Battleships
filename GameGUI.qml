import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 1.2


ApplicationWindow {
    width: Screen.desktopAvailableWidth
    height: Screen.desktopAvailableHeight
    visible: true
    title: "Battleships"


    // Draw background
    Rectangle {
        id: background
        anchors.fill: parent
        color: "gray"
    }

    //    SettingsDialog {
    //        state: "dialog_visible"
    //    }

    Flow {
        anchors.fill: parent
        spacing: 50
        anchors.margins: 10

        GameBoardView {
            id: own
            availableWidth: parent.width / 2
            availableHeight: parent.height
            name: "Christian"
        }

        // List of ships to place.
        Rectangle {
            id: infoBoard
            width: own.width * 0.75
            height: own.height
            gradient: Gradient {
                GradientStop { position: 0; color: "lightgreen" }
                GradientStop { position: 1; color: "green" }
            }

            border.color: "black"
            border.width: 3
            radius: 10

            Column {
                anchors.fill: parent
                anchors.margins: 20
                spacing: 30 * (parent.height / 480)
                property string imageSrc: "qrc:resources/Ship.png"

                // Title
                Text {
                    font.bold: true
                    font.pixelSize: 26 * (parent.height / 480)
                    text: qsTr("Place your ships !")
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                // Spacer (vertical)
                Rectangle {
                    width: 10
                    height: 50 * (parent.height / 480)
                    color: "transparent"
                }
                // Ship images
                Image {
                    id: airCarrier
                    width: own.cellSide * 5
                    height: own.cellSide
                    source: parent.imageSrc
                    anchors.horizontalCenter: parent.horizontalCenter
                    MouseArea {
                        anchors.fill: parent
                        onClicked: parent.opacity = 0.5
                    }
                }
                Image {
                    id: battleship
                    width: own.cellSide * 4
                    height: own.cellSide * 4/5
                    source: parent.imageSrc
                    anchors.horizontalCenter: parent.horizontalCenter
                    MouseArea {
                        anchors.fill: parent
                        onClicked: parent.opacity = 0.5
                    }
                }
                Image {
                    id: destroyer
                    width: own.cellSide * 3
                    height: own.cellSide * 3/5
                    source: parent.imageSrc
                    anchors.horizontalCenter: parent.horizontalCenter
                    MouseArea {
                        anchors.fill: parent
                        onClicked: parent.opacity = 0.5
                    }
                }
                Image {
                    id: submarine
                    width: own.cellSide * 3
                    height: own.cellSide * 3/5
                    source: parent.imageSrc
                    anchors.horizontalCenter: parent.horizontalCenter
                    MouseArea {
                        anchors.fill: parent
                        onClicked: parent.opacity = 0.5
                    }
                }
                Image {
                    id: jole
                    width: own.cellSide * 2
                    height: own.cellSide * 2/5
                    source: parent.imageSrc
                    anchors.horizontalCenter: parent.horizontalCenter
                    MouseArea {
                        anchors.fill: parent
                        onClicked: parent.opacity = 0.5
                    }
                }
            } // END column
        } // END rectangle
    } // END flow
}


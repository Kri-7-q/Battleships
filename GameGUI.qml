import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 1.2
import Models 1.0

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

    GameBoardModel {
        id: gameBoardModel
        columns: 10
        rows: 10
    }

    Rectangle {
        id: screen
        anchors.fill: parent
        color: "transparent"
        property bool placeShip: false

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

                    Text {
                        font.bold: true
                        font.pixelSize: 26 * (parent.height / 480)
                        text: qsTr("Place your ships !")
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Rectangle {
                        width: 10
                        height: 50 * (parent.height / 480)
                        color: "transparent"
                    }

                    Image {
                        id: airCarrier
                        width: own.cellSide * 5
                        height: own.cellSide
                        source: "file:/Users/Christian/Pictures/Schiff.png"
                        anchors.horizontalCenter: parent.horizontalCenter
                        MouseArea {
                            anchors.fill: parent
                            onClicked:  {
                                screen.placeShip = true
                                ship.width = parent.width
                                ship.height = parent.height
                                parent.destroy()
                            }
                        }
                    }
                    Image {
                        id: battleship
                        width: own.cellSide * 4
                        height: own.cellSide * (4/5)
                        source: "file:/Users/Christian/Pictures/Schiff.png"
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Image {
                        id: destroyer
                        width: own.cellSide * 3
                        height: own.cellSide * (3/5)
                        source: "file:/Users/Christian/Pictures/Schiff.png"
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Image {
                        id: submarine
                        width: own.cellSide * 3
                        height: own.cellSide * (3/5)
                        source: "file:/Users/Christian/Pictures/Schiff.png"
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Image {
                        id: jole
                        width: own.cellSide * 2
                        height: own.cellSide * (2/5)
                        source: "file:/Users/Christian/Pictures/Schiff.png"
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                } // END column
            } // END rectangle
        } // END flow

        MouseArea {
            id: screenMouseArea
            enabled: screen.placeShip
            hoverEnabled: screen.placeShip
            onMouseXChanged: ship.x = mouseX
            onMouseYChanged: ship.y = mouseY
            anchors.fill: parent
        }

        Rectangle {
            id: ship
            visible: screen.placeShip
            color: "transparent"
            Image {
                anchors.fill: parent
                source: "file:/Users/Christian/Pictures/Schiff.png"
            }
        }

    } // END screen
}


import QtQuick 2.0
import QtQuick.Controls 1.2
import Controler 1.0
import Models 1.0


ApplicationWindow {
    width: 960
    height: 480
    visible: true
    title: "Battleships"

    Controler {
        id: controler
    }

    GameBoardModel {
        id: gameBoardModel
        columns: 10
        rows: 10
    }

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
        id: placeShipsView
        anchors.fill: parent
        spacing: 50
        anchors.margins: 10
        property double scaleFactor: (width / 900) < (height / 480) ? (width / 900) : (height / 480)

        GameBoardView {
            id: placeShipBoard
            availableWidth: parent.width / 2
            availableHeight: parent.height
            name: "Christian"
        }

        // List of ships to place.
        Rectangle {
            id: infoBoard
            width: parent.width / 2 * 0.75
            height: placeShipBoard.height
            gradient: Gradient {
                GradientStop { position: 0; color: "lightgreen" }
                GradientStop { position: 1; color: "green" }
            }

            border.color: "black"
            border.width: 3
            radius: 10

            // Info board to show ships which are to place on game board.
            Column {
                anchors.fill: parent
                anchors.margins: 20
                spacing: 30 * placeShipsView.scaleFactor
                property string imageSrc: "qrc:resources/Ship.png"

                ListModel {
                    id: shipModel
                    property int index: 0
                    ListElement { name: "Air Carrier"; length: 5 }
                    ListElement { name: "Battleship"; length: 4 }
                    ListElement { name: "Destroyer"; length: 3 }
                    ListElement { name: "Submarine"; length: 3 }
                    ListElement { name: "Cruiser"; length: 2 }
                }

                // Title
                Text {
                    font.bold: true
                    font.pixelSize: 26 * placeShipsView.scaleFactor
                    text: qsTr("Place your ships !")
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                // Spacer (vertical)
                Rectangle {
                    width: 10
                    height: 50 * placeShipsView.scaleFactor
                    color: "transparent"
                }
                // Ships name
                Text {
                    font.pixelSize: 20 * placeShipsView.scaleFactor
                    text: shipModel.get(shipModel.index).name
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                // Ship images
                Image {
                    id: ship
                    width: placeShipBoard.cellSide * shipModel.get(shipModel.index).length
                    height: placeShipBoard.cellSide
                    source: parent.imageSrc
                    fillMode: Image.PreserveAspectFit
                    anchors.horizontalCenter: parent.horizontalCenter
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            parent.opacity = 0.5
                        }
                    }
                }
                // Spacer (vertical)
                Rectangle {
                    width: 20
                    height: 10 * placeShipsView.scaleFactor
                    color: "transparent"
                }
                // Info how to rotate ships.
                Text {
                    font.pixelSize: 12 * (parent.height / 480)
                    text: qsTr("Press right mouse button to rotate.")
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                // Spacer
                Rectangle {
                    width: 20
                    height: 10 * placeShipsView.scaleFactor
                    color: "transparent"
                }
                // Button to start game when ships placed.
                Button {
                    id: startButton
                    visible: false
                    width: 100 * placeShipsView.scaleFactor
                    height: 30 * placeShipsView.scaleFactor
                    text: qsTr("Start game")
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            } // END column
        } // END rectangle
    } // END flow
}


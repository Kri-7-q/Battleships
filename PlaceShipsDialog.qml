import Controler 1.0
import QtQuick 2.0
import QtQuick.Controls 1.2


Flow {
    id: placeShipsView
    anchors.fill: parent
    spacing: 50
    anchors.margins: 10
    property bool delegateMouseAreaEnabled: true
    property int delegateAngel: 0
    property bool allShipsSet: false
    onAllShipsSetChanged: if (allShipsSet) { btnPlaceShipsFinished.text = "Next" }

    GameBoardView {
        id: placeShipBoard
        availableWidth: parent.width / 2
        availableHeight: parent.height
        delegate: PlaceShipDelegate { width: placeShipBoard.cellSide; height: placeShipBoard.cellSide; }
        model: gameBoardModel
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
            scale: window.scale
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
                font.pixelSize: 26
                text: qsTr("Place your ships !")
                anchors.horizontalCenter: parent.horizontalCenter
            }
            // Spacer (vertical)
            Spacer {
                height: 50
            }

            // Ships name
            Text {
                id: shipName
                font.pixelSize: 20
                text: shipModel.get(shipModel.index).name
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Spacer {
                height: 10
            }

            // Ship images
            Image {
                id: shipImage
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
            Spacer {
                height: 30
            }

            // Info how to rotate ships.
            Text {
                font.pixelSize: 12
                text: qsTr("Press right mouse button to rotate.")
                anchors.horizontalCenter: parent.horizontalCenter
            }
            // Spacer
            Spacer {
                height: 60
            }

            // Button to start game when ships placed.
            Button {
                id: btnPlaceShipsFinished
                visible: true
                width: 100
                height: 30
                isDefault: true
                text: qsTr("Place randomly")
                style: CustomButton { color: "orange" }
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: {
                    if (placeShipsView.allShipsSet) {
                        // Ships placed go to next view
                        if (controler.playerMode === Controler.SinglePlayer) {
                            controler.localePlayersTurn = true
                            controler.currentView = "GamePlayDialog"
                        } else {
                            controler.currentView = "NetworkDialog"
                        }
                    } else {
                        // Place ships randomly
                        controler.randomlyPlaceShips(gameBoardModel)
                        placeShipsView.allShipsSet = true;
                    }
                }
            }
        } // END column
    } // END rectangle

    states: [
        State {
            name: "active"
            when: controler.currentView === "PlaceShipsDialog"
            PropertyChanges { target: placeShipsDialog; visible: true; }
            PropertyChanges { target: btnPlaceShipsFinished; enabled: true; }
        },
        State {
            name: "inactive"
            when: controler.currentView !== "PlaceShipsDialog"
            PropertyChanges { target: placeShipsDialog; visible: false }
        }

    ]

} // END flow

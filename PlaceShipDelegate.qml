import QtQuick 2.0
import Models 1.0


Rectangle {
    id: boardDelegate
    color: "transparent"
    border.width: 1
    border.color: "black"

    // Draw Image with field content.
    Image {
        width: parent.width * 0.85
        height: parent.height * 0.85
        anchors.centerIn: parent
        source: "qrc:resources/placedShip.png"
        visible: placeShips
    }

    // Pointer to position a ship.
    Image {
        id: shipPointer
        visible: false
        anchors.fill: parent
        transformOrigin: Item.Center
        source: "qrc:resources/DirectionPointer.png"
    }

    MouseArea {
        id: delegateMouseArea
        enabled: placeShipsView.delegateMouseAreaEnabled
        anchors.fill: boardDelegate
        hoverEnabled: enabled
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onEntered: {
            shipPointer.rotation = placeShipsView.delegateAngel
            shipPointer.visible = true
        }
        onExited: {
            shipPointer.visible = false
        }
        onClicked: {
            // Right mouse button pressed to rotate ship.
            if (mouse.button == Qt.RightButton) {
                placeShipsView.delegateAngel += 90
                if (placeShipsView.delegateAngel >= 360)     placeShipsView.delegateAngel = 0
                shipPointer.rotation = placeShipsView.delegateAngel
            }
            // Left mouse Button pressed. Place ship or end dialog.
            if (mouse.button == Qt.LeftButton) {
                var length = shipModel.get(shipModel.index).length
                var name = shipModel.get(shipModel.index).name
                if(gameBoardModel.placeShip(length, name, index, placeShipsView.delegateAngel)) {
                    if (shipModel.count > shipModel.index + 1) {
                        shipModel.index += 1
                    } else {
                        boardDelegate.state = "endPlaceShipsDialog"
                    } // END else
                } // END if
            }// END if (left mouse button)
        }// END onClicked
    } // END mouse area
    states: [
        State {
            name: "endPlaceShipsDialog"
            PropertyChanges { target: startButton; visible: true; }
            PropertyChanges { target: shipName; text: qsTr("No more ships available."); }
            PropertyChanges { target: shipImage; visible: false; }
            PropertyChanges { target: shipPointer; visible: false; }
            PropertyChanges { target: placeShipsView; delegateMouseAreaEnabled: false }
        }

    ]
} // END delegate rectangle


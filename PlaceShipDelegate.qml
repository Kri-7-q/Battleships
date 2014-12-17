import QtQuick 2.0
import Models 1.0


Rectangle {
    id: boardDelegate
    color: "transparent"
    border.width: 1
    border.color: "black"
    property int angel: 0

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
        id: cellMouseArea
        anchors.fill: boardDelegate
        hoverEnabled: enabled
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onEntered: {
            shipPointer.rotation = board.pointerAngel
            shipPointer.visible = true
        }
        onExited: {
            shipPointer.visible = false
        }
        onClicked: {
            if (mouse.button == Qt.RightButton) {
                board.pointerAngel += 90
                if (board.pointerAngel >= 360)     board.pointerAngel = 0
                shipPointer.rotation = board.pointerAngel
            }
            if (mouse.button == Qt.LeftButton) {
                var length = shipModel.get(shipModel.index).length
                var name = shipModel.get(shipModel.index).name
                if(gameBoardModel.placeShip(length, name, index, board.pointerAngel)) {
                    if (shipModel.count > shipModel.index) {
                        shipModel.index += 1
                    }
                    if (shipModel.index == shipModel.count-1) {
                        startButton.visible = true
                    }
                }
            }
        }
    } // END mouse area
} // END delegate rectangle


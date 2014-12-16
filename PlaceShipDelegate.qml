import QtQuick 2.0
import Models 1.0

Rectangle {
    id: boardDelegate
    color: "transparent"
    border.width: 1
    border.color: "black"
    anchors.margins: 1
    property int fieldIndex: index
    property int angel: 0

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
        }
    } // END mouse area
} // END delegate rectangle

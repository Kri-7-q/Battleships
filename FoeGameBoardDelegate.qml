import QtQuick 2.0
import Models 1.0

Rectangle {
    id: foeGameBoardDelegate
    width: playGameBoard.cellSide
    height: playGameBoard.cellSide
    color: "transparent"
    border.color: "black"
    border.width: 1

    Image {
        id: fieldImageHiddenField
        visible: display == 1 ? true : false
        width: parent.width * 0.8
        height: parent.height * 0.8
        anchors.centerIn: parent
        source: "qrc:resources/hiddenField.png"
    }
    Image {
        id: fieldImageHiddenShip
        visible: display == 2 ? true : false
        width: parent.width * 0.8
        height: parent.height * 0.8
        anchors.centerIn: parent
        source: "qrc:resources/hiddenShip.png"
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.CrossCursor
        onEntered: {
            foeGameBoardDelegate.color = "white"
            foeGameBoardDelegate.opacity = 0.4
        }
        onExited: {
            foeGameBoardDelegate.opacity = 1
            foeGameBoardDelegate.color = "transparent"
        }
        onClicked: {
            if (mouse.button == Qt.LeftButton) {
                gameBoardModelFoe.shootAt(index)
            }
        }
    }
}

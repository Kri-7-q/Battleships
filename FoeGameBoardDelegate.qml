import QtQuick 2.0
import Models 1.0

Rectangle {
    id: foeGameBoardDelegate
    width: playGameBoard.cellSide
    height: playGameBoard.cellSide
    color: "transparent"
    border.color: "black"
    border.width: 1
    state: "mouseExited"

    Image {
        id: fieldImage
        visible: display !== GameBoardModel.EmptyField
        width: parent.width * 0.8
        height: parent.height * 0.8
        anchors.centerIn: parent
        source: {
            switch (display) {
            case GameBoardModel.HiddenField:
                return "qrc:resources/hiddenField.png"
                break
            case GameBoardModel.HiddenShip:
                return "qrc:resources/hiddenShip.png"
                break
            default:
                return "qrc:resources/emptyField.png"
                break
            }
        }
    }

    MouseArea {
        enabled: controler.localePlayersTurn
        onEnabledChanged: {
            if (enabled == false) {
                foeGameBoardDelegate.state = "mouseExited"
            }
        }

        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.CrossCursor
        onEntered: foeGameBoardDelegate.state = "mouseEnterd"
        onExited: foeGameBoardDelegate.state = "mouseExited"
        onClicked: {
            if (mouse.button == Qt.LeftButton) {
                controler.playersShoot(index)
            }
        }
    }

    states: [
        State {
            name: "mouseEnterd"
            PropertyChanges { target: foeGameBoardDelegate; color: "white"; opacity: 0.4; }
        },
        State {
            name: "mouseExited"
            PropertyChanges { target: foeGameBoardDelegate; color: "transparent"; opacity: 1; }
        }
    ]
}

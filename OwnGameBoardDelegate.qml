import QtQuick 2.0
import Models 1.0

Rectangle {
    width: ownGameBoard.cellSide
    height: ownGameBoard.cellSide
    color: "transparent"
    border.color: "black"
    border.width: 1

    Image {
        id: fieldState
        width: parent.width * 0.8
        height: parent.height * 0.8
        visible: displayAll == GameBoardModel.emptyField ? false : true
        source: {
            switch (displayAll) {
            case GameBoardModel.hiddenField:
                return "qrc:resources/hiddenField.png"
                break
            case GameBoardModel.hiddenShip:
                return "qrc:resources/hiddenShip.png"
                break
            case GameBoardModel.placedShip:
                return "qrc:resources/placedShip.png"
                break
            default:
                return "qrc:resources/emptyField.png"
                break
            }
        }
    }
}

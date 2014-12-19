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
        visible: displayAll === GameBoardModel.EmptyField ? false : true
        source: {
            switch (displayAll) {
            case GameBoardModel.HiddenField:
                return "qrc:resources/hiddenField.png"
                break
            case GameBoardModel.HiddenShip:
                return "qrc:resources/hiddenShip.png"
                break
            case GameBoardModel.PlacedShip:
                return "qrc:resources/placedShip.png"
                break
            default:
                return "qrc:resources/emptyField.png"
                break
            }
        }
    }
}

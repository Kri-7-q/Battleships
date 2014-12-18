import QtQuick 2.0
import QtQuick.Controls 1.2
import Controler 1.0
import Models 1.0


ApplicationWindow {
    id: window
    width: 900
    height: 480
    visible: true
    title: "Battleships"
    property double scaleWidth: width / 900
    property double scaleHeight: height / 480
    property double scale: scaleWidth > scaleHeight ? scaleHeight : scaleWidth

    Controler {
        id: controler
        playerName: "Christian"
    }

    // ------------------------------
    // Models
    // ------------------------------
    GameBoardModel {
        id: gameBoardModel
        columns: 10
        rows: 10
    }
    GameBoardModel {
        id: gameBoardModelFoe
        columns: 10
        rows: 10
    }

    // Draw background
    Rectangle {
        id: background
        anchors.fill: parent
        color: "black"
    }

    // ----------------------------------------------------------
    // Dialogs
    // -----------------------------------------------------------
    // Dialog to insert my name.
    PlayerNameDialog {
        // Background color "gold".
        visible: false
    }

    // Dialog to specify the game board size.
    BoardSizeDialog {
        visible: false
        width: parent.width * 0.8
        height: parent.height * 0.8
        anchors.centerIn: parent
    }

    // Dialog to place ships.
    PlaceShipsDialog {
        visible: false
    }

    // Game play GUI
    Flow {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 40
        property int widthBoardFoe: (width - 40) * 0.7
        property int widthBoardOwn: (width - 40) * 0.3

        GameBoardView {
            id: playGameBoard
            availableWidth: parent.widthBoardFoe
            availableHeight: parent.height
            name: qsTr("Foe")
            delegate: FoeGameBoardDelegate { }
            model: gameBoardModelFoe
        }

        Column {
            width: parent.widthBoardOwn
            height: parent.height
            anchors.margins: 10

            GameBoardView {
                id: ownGameBoard
                availableWidth: parent.width
                availableHeight: parent.height / 2
                name: controler.playerName
                delegate: OwnGameBoardDelegate { }
                model: gameBoardModel
            }
        }
    }
}


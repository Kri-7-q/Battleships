import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Window 2.0
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


    // ------------------------------
    // Models
    // ------------------------------
    GameBoardModel {
        id: gameBoardModel
        columns: 10
        rows: 10
        onDestroyedShipNameChanged: {
            var text = "Your " + destroyedShipName + " was desroyed !"
            gamePlayDialog.infoTextArea.append(text)
        }
    }
    GameBoardModel {
        id: gameBoardModelFoe
        columns: 10
        rows: 10
        onDestroyedShipNameChanged: {
            var text = "You destroyed the " + destroyedShipName + " of your foe !"
            gamePlayDialog.infoTextArea.append(text)
        }
    }

    // Draw background
    Rectangle {
        id: background
        anchors.fill: parent
        color: "black"
    }

    // -----------------------------
    // Controler
    // -----------------------------
    Controler {
        id: controler
        playersGameBoard: gameBoardModel
        foesGameBoard: gameBoardModelFoe
        onInfoTextChanged: gamePlayDialog.infoTextArea.append(infoText)
    }

    // ----------------------------------------------------------
    // Dialogs
    // -----------------------------------------------------------
    // Dialog to insert my name.
    PlayerNameDialog {
        // Background color "gold".
        id: nameDialog
        visible: false
        state: "active"
    }

    // Dialog to specify the game board size.
    BoardSizeDialog {
        id: boardSizeDialog
        visible: false
        width: parent.width * 0.8
        height: parent.height * 0.8
        anchors.centerIn: parent
        state: "inactive"
    }

    // Dialog to place ships.
    PlaceShipsDialog {
        id: placeShipsDialog
        visible: false
        state: "inactive"
    }

    // Game play GUI
    GamePlayDialog {
        id: gamePlayDialog
        visible: false
        state: "inactive"
    }

    // Game over dialog
    GameOverDialog {
        id: gameOverDialog
        width: 500
        height: 200
        anchors.centerIn: parent
    }
}


import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Window 2.0
import Models 1.0
import Controler 1.0


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
        playerName: "Christian"
        onShipDestroyed: {
            var text = "Your " + destroyedShipName + " sunk !"
            gamePlayDialog.infoTextArea.append(text)
        }
    }
    GameBoardModel {
        id: gameBoardModelFoe
        columns: 10
        rows: 10
        playerName: "Foe"
        onShipDestroyed: {
            var text = destroyedShipName + " of enemy sunk !"
            gamePlayDialog.infoTextArea.append(text)
        }
    }

//    // -----------------------------
//    // Controler
//    // -----------------------------
//    Controler {
//        id: controler
//        objectName: "Battleships"
//        playersGameBoard: gameBoardModel
//        foesGameBoard: gameBoardModelFoe
//        onInfoTextChanged: gamePlayDialog.infoTextArea.append(infoText)
//    }

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
        id: nameDialog
        visible: false
        state: "active"
    }

    // Dialog to specify the game board size.
    BoardSizeDialog {
        id: boardSizeDialog
        visible: false
        state: "inactive"
    }

    // Dialog to place ships.
    PlaceShipsDialog {
        id: placeShipsDialog
        visible: false
        state: "inactive"
    }

    // NetworkDialog
    NetworkDialog {
        id: networkDialog
        visible: false
    }

    ShowGameOffer {
        id: showGameOffer
        visible: false
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


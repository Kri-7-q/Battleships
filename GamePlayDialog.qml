import QtQuick 2.0
import QtQuick.Controls 1.2

Flow {
    visible: false
    anchors.fill: parent
    anchors.margins: 10
    spacing: 40
    property int widthBoardFoe: (width - 40) * 0.7
    property int widthBoardOwn: (width - 40) * 0.3
    property alias infoTextArea: infoField

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
        spacing: 10

        GameBoardView {
            id: ownGameBoard
            availableWidth: parent.width
            availableHeight: parent.height / 2
            name: controler.playerName
            delegate: OwnGameBoardDelegate { }
            model: gameBoardModel
            anchors.horizontalCenter: parent.horizontalCenter
        }

        TextArea {
            id: infoField
            width: parent.width
            height: parent.height / 2 - 30
            readOnly: true
            textColor: "white"
            backgroundVisible: false
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    states: [
        State {
            name: "inactive"
        },
        State {
            name: "active"
            PropertyChanges { target: gamePlayDialog; visible: true; }
        },
        State {
            when: controler.isGameOver
            PropertyChanges { target: gameOverDialog; state: "active"; }
        }
    ]

}

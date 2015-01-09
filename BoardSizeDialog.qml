import QtQuick 2.0
import QtQuick.Controls 1.2
import Controler 1.0


// Dialog to enter game board size and network address.
Rectangle {
    width: parent.width * 0.8
    height: parent.height * 0.8
    anchors.centerIn: parent
    color: "goldenrod"
    border.color: "gray"
    border.width: 3
    property int margin: 20
    anchors.margins: margin
    radius: 20
    scale: window.scale

    Column {
        id: itemColumn
        anchors.centerIn: parent
        spacing: 10
        height: infoText1.height + infoText2.height + inputControlRow.height + vertSpacer3.height + submitButtonRow.height
        scale: window.scale

        Text {
            id: infoText1
            font.pixelSize: 24
            text: qsTr("Please insert the size of your game board.")
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Text {
            id: infoText2
            font.pixelSize: 11
            text: qsTr("Min. 5 x 5 and max. size 20 x 20 Fields.")
            anchors.horizontalCenter: parent.horizontalCenter
        }
        // Input fields to specify the size of game board.
        Row {
            id: inputControlRow
            height: 27
            spacing: 10
            anchors.horizontalCenter: parent.horizontalCenter
            TextField {
                id: inputGameBoradWidth
                width: 50
                height: parent.height
                placeholderText: qsTr("width")
                horizontalAlignment: TextInput.AlignHCenter
                validator: IntValidator { bottom: 5; top: 20 }
            }
            Rectangle {
                width: 10
                height: parent.height
                color: "transparent"
                Text {
                    text: "x"
                    anchors.centerIn: parent
                }
            }
            TextField {
                id: inputGameBoardHeight
                width: 50
                height: parent.height
                placeholderText: qsTr("height")
                horizontalAlignment: TextInput.AlignHCenter
                validator: IntValidator { bottom: 5; top: 20 }
            }
        }
        Rectangle {
            id: vertSpacer3
            width: parent.width
            height: 20
            color: "transparent"
        }

        // Submit buttons for multi and single player mode
        Row {
            id: submitButtonRow
            height: 40

            Button {
                id: singlePlayerSubmitButton
                width: 200
                height: submitButtonRow.height
                text: qsTr("Single Player")
                style: CustomButton { fontSize: 20 }
                onClicked: {
                    controler.playerMode = Controler.SinglePlayer
                    gameBoardModel.columns = inputGameBoradWidth.text
                    gameBoardModel.rows = inputGameBoardHeight.text
                    gameBoardModelFoe.columns = gameBoardModel.columns
                    gameBoardModelFoe.rows = gameBoardModel.rows
                    controler.randomlyPlaceShips(gameBoardModelFoe)
                    controler.currentView = "PlaceShipsDialog"
                }
            }
            Rectangle {
                width: 50
                height: 2
                color: "transparent"
            }
            Button {
                id: multiplayerSubmitButtom
                width: 200
                height: submitButtonRow.height
                text: qsTr("Multi Player")
                style: CustomButton { fontSize: 20 }
                onClicked: {
                    controler.playerMode = Controler.MultiPlayer
                    gameBoardModel.columns = inputGameBoradWidth.text
                    gameBoardModel.rows = inputGameBoardHeight.text
                    controler.currentView = "PlaceShipsDialog"
                }
            }
        }
    }

    states: [
        State {
            name: "inactive"
            when: controler.currentView !== "BoardSizeDialog"
            PropertyChanges { target: boardSizeDialog; visible: false; }
        },
        State {
            name: "active"
            when: controler.currentView === "BoardSizeDialog"
            PropertyChanges { target: boardSizeDialog; visible: true; }
            PropertyChanges { target: singlePlayerSubmitButton; enabled: true; }
            PropertyChanges { target: multiplayerSubmitButtom; enabled: true; }
            PropertyChanges { target: inputGameBoradWidth; focus: true; }
        }
    ]

}


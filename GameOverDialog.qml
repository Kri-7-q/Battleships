import QtQuick 2.0
import QtQuick.Controls 1.2

Rectangle {
    visible: false
    anchors.centerIn: parent
    scale: window.scale
    state: "inactive"
    color: "darkseagreen"
    border.color: "gray"
    border.width: 3
    radius: 10

    Column {
        spacing: 30
        anchors.centerIn: parent

        Text {
            font.pixelSize: 20
            text: qsTr("The game is over !")
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Text {
            font.pixelSize: 30
            text: qsTr(controler.winnerName + " has won the Game.")
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            Button {
                width: 100
                text: qsTr("Restart")
                style: CustomButton { }
                onClicked: {
                    gameBoardModel.removeAll()
                    gameBoardModelFoe.removeAll()
                    gameOverDialog.state = "restart"
                }
            }
            Rectangle {
                width: 20
                height: 10
                color: "transparent"
            }

            Button {
                width: 100
                text: qsTr("Exit")
                style: CustomButton { }
                onClicked: window.close()
            }
        } // END row
    } // END column

    states: [
        State {
            name: "inactive"
        },
        State {
            name: "active"
            PropertyChanges { target: gameOverDialog; visible: true; }
        },
        State {
            name: "restart"
            PropertyChanges { target: gameOverDialog; visible: false; }
            PropertyChanges { target: gamePlayDialog; visible: false; }
            PropertyChanges { target: nameDialog; visible: true; }
        }
    ]
} // End rectangle

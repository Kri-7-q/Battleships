import QtQuick 2.0
import QtQuick.Controls 1.2


Item {
    id: dialog
    anchors.fill: parent
    property double factorWidth: width / 960
    property double factorHeight: height / 480

    // Dialog to enter players name
    Item {
        id: nameDialog

        width: dialogColumn.width
        height: dialogColumn.height
        anchors.centerIn: parent

        Column {
            id: dialogColumn
            width: dialog.width * 0.85
            // Game title
            Item {
                id: shadowedTitle
                property int shadowOffset: height * 0.08
                height: dialog.height * 0.2
                width: titleShadow.width + shadowOffset
                anchors.horizontalCenter: parent.horizontalCenter
                Text {
                    id: titleShadow
                    font.pixelSize: shadowedTitle.height
                    font.bold: true
                    text: "Battleships"
                    color: "black"
                }
                Text {
                    id: redTitle
                    y: titleShadow.y - parent.shadowOffset
                    x: titleShadow.x + parent.shadowOffset
                    font.pixelSize: shadowedTitle.height
                    font.bold: true
                    text: "Battleships"
                    color: "red"
                }
            }
            Rectangle {
                id: vertSpacer
                height: dialog.height * 0.1
                width: 200
                color: "transparent"
            }
            // Lable for input player name.
            Text {
                id: childLable
                height: dialog.height * 0.1
                font.pixelSize: height - 4
                text: qsTr("Enter your name :")
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Rectangle {
                id: vertSpacer2
                height: dialog.height * 0.05
                width: 200
                color: "transparent"
            }
            // Text field and ok button to enter player name.
            Row {
                id: nameForm
                height: dialog.height * 0.1
                anchors.horizontalCenter: dialogColumn.horizontalCenter

                TextField {
                    id: playerName
                    height: nameForm.height
                    width: dialogColumn.width * 0.5
                    font.pixelSize: height * 0.75
                    text: "Fritz"
                    focus: true
                }
                Rectangle {
                    id: horzSpacer
                    width: dialogColumn.width * 0.02
                    height: nameForm.height
                    color: "transparent"
                }

                Button {
                    id: submitButton
                    text: "Ok"
                    height: nameForm.height
                    width: dialogColumn.width * 0.2
                    onClicked: dialog.state = "sizeAndNetwork_visible"
                }
            }
        }
    }

    // Dialog to enter game board size and network address.
    Item {
        id: sizeAndNetworkDialog
        width: itemColumn.width
        height: itemColumn.height
        anchors.centerIn: parent

        Column {
            id: itemColumn
            width: dialog.width * 0.8
            spacing: 10

            Text {
                font.pixelSize: 24 * dialog.factorWidth
                text: qsTr("Please insert the size of your game board.")
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Text {
                font.pixelSize: 11 * dialog.factorWidth
                text: qsTr("Min. 5 x 5 and max. size 20 x 20 Fields.")
                anchors.horizontalCenter: parent.horizontalCenter
            }
            // Input fields to specify the size of game board.
            Row {
                height: 27 * dialog.factorHeight
                spacing: 10
                anchors.horizontalCenter: parent.horizontalCenter
                TextField {
                    id: inputGameBoradWidth
                    width: 50 * dialog.factorWidth
                    height: parent.height
                    placeholderText: qsTr("width")
                    horizontalAlignment: TextInput.AlignHCenter
                    //inputMask: "99"
                    validator: IntValidator { bottom: 5; top: 20 }
                }
                Rectangle {
                    width: 10 * dialog.factorWidth
                    height: parent.height
                    color: "transparent"
                    Text {
                        text: "x"
                        anchors.centerIn: parent
                    }
                }
                TextField {
                    id: inputGameBoardHeight
                    width: 50 * dialog.factorWidth
                    height: parent.height
                    placeholderText: qsTr("height")
                    horizontalAlignment: TextInput.AlignHCenter
                    //inputMask: "99"
                    validator: IntValidator { bottom: 5; top: 20 }
                }
            }
            Rectangle {
                id: vertSpacer3
                width: parent.width
                height: 20 * dialog.factorHeight
                color: "transparent"
            }

            Button {
                width: parent.width * 0.3
                height: 40 * dialog.factorHeight
                text: qsTr("Start game")
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }

    // States to switch to another view.
    states: [
        State {
            name: "dialog_visible"
            PropertyChanges {
                target: nameDialog
                visible: true
            }
            PropertyChanges {
                target: sizeAndNetworkDialog
                visible: false
            }
        },
        State {
            name: "sizeAndNetwork_visible"
            PropertyChanges {
                target: sizeAndNetworkDialog
                visible: true
            }
            PropertyChanges {
                target: nameDialog
                visible: false
            }
        }
    ]

}

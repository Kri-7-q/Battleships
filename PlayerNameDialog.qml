import QtQuick 2.0
import QtQuick.Controls 1.2


// Dialog to enter players name
Rectangle {
    width: parent.width * 0.8
    height: dialogColumn.height + 100
    anchors.centerIn: parent
    scale: window.scale
    color: "goldenrod"
    border.color: "gray"
    border.width: 3
    radius: 10

    Column {
        id: dialogColumn
        anchors.centerIn: parent
        height: shadowedTitle.height + vertSpacer.height + childLable.height + vertSpacer2.height + nameForm.height

        // Game title
        Item {
            id: shadowedTitle
            property int shadowOffset: 3
            height: 100
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
            height: 100
            width: 200
            color: "transparent"
        }
        // Lable for input player name.
        Text {
            id: childLable
            height: 30
            font.pixelSize: height - 4
            text: qsTr("Enter your name :")
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Rectangle {
            id: vertSpacer2
            height: 20
            width: 200
            color: "transparent"
        }
        // Text field and ok button to enter player name.
        Row {
            id: nameForm
            height: 40
            anchors.horizontalCenter: dialogColumn.horizontalCenter

            TextField {
                id: playerName
                height: nameForm.height
                width: 350
                font.pixelSize: 26
                text: "Fritz"
            }
            Rectangle {
                id: horzSpacer
                width: 20
                height: nameForm.height
                color: "transparent"
            }

            Button {
                id: submitButton
                text: "Ok"
                height: nameForm.height
                width: 150
                isDefault: true
                style: CustomButton {  }
                onClicked: {
                    controler.playerName = playerName.text
                    nameDialog.state = "switch"
                }
            }
        }
    }

    states: [
        State {
            name: "active"
            PropertyChanges { target: nameDialog; visible: true; }
            PropertyChanges { target: playerName; focus: true; }
            PropertyChanges { target: submitButton; enabled: true; }
        },
        State {
            name: "switch"
            PropertyChanges { target: nameDialog; visible: false; }
            PropertyChanges { target: boardSizeDialog; state: "active"; }
        }

    ]

}

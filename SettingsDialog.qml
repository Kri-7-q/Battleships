import QtQuick 2.0
import QtQuick.Controls 1.2


// Dialog to enter players name
Item {
    id: dialog

    width: dialogColumn.width
    height: dialogColumn.height

    Column {
        id: dialogColumn
        width: background.width * 0.85
        // Game title
        Item {
            id: shadowedTitle
            property int shadowOffset: height * 0.08
            height: background.height * 0.2
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
            height: background.height * 0.1
            width: 200
            color: "transparent"
        }
        // Lable for input player name.
        Text {
            id: childLable
            height: background.height * 0.1
            font.pixelSize: height - 4
            text: qsTr("Enter your name :")
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Rectangle {
            id: vertSpacer2
            height: background.height * 0.05
            width: 200
            color: "transparent"
        }
        // Text field and ok button to enter player name.
        Row {
            id: nameForm
            height: background.height * 0.1
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
                onClicked: dialog.state = "dialog_invisible"
            }
        }
    }
    // States to switch to another view.
    states: [
        State { name: "dialog_visible"; PropertyChanges { target: dialog; visible: true } },
        State { name: "dialog_invisible"; PropertyChanges { target: dialog; visible: false } }
    ]
}

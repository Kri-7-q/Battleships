import QtQuick 2.0
import QtQuick.Controls 1.2

Rectangle {
    width: parent.width * 0.8
    height: parent.height * 0.8
    anchors.centerIn: parent
    color: "goldenrod"
    border.color: "gray"
    border.width: 3
    radius: 20
    scale: window.scale
    property var model: controler.gameOfferValueList()
    onModelChanged: { btnAgree.enabled = true; btnNotAgree.enabled }
    property int fontSize: 25
    property int textWidth: 150
    property string headerColor: "black"
    property string valueColor: "brown"

    Column {
        anchors.centerIn: parent
        spacing: 30
        scale: window.scale

        Row {
            spacing: 30

            Text {
                width: textWidth
                color: headerColor
                font.pixelSize: fontSize
                text: qsTr("Player name :")
            }

            Text {
                color: valueColor
                font.pixelSize: fontSize
                text: qsTr(model[0])
            }
        }

        Row {
            spacing: 30
            Text {
                width: textWidth
                color: headerColor
                font.pixelSize: fontSize
                text: qsTr("Board size X :")
            }

            Text {
                color: valueColor
                font.pixelSize: fontSize
                text: qsTr(model[1])
            }
        }

        Row {
            spacing: 30

            Text {
                width: textWidth
                color: headerColor
                font.pixelSize: fontSize
                text: qsTr("Board size Y :")
            }

            Text {
                color: valueColor
                font.pixelSize: fontSize
                text: qsTr(model[2])
            }
        }

        Row {
            spacing: 30

            Text {
                width: textWidth
                color: headerColor
                font.pixelSize: fontSize
                text: qsTr("Ship list :")
            }

            Text {
                color: valueColor
                font.pixelSize: fontSize
                text: qsTr(model[3])
            }
        }

        Row {
            spacing: 200

            Button {
                id: btnNotAgree
                enabled: false
                width: 100
                height: 30
                text: qsTr("Don't agree")
                style: CustomButton {}
                onClicked: controler.sendGameOfferReplay(controler.playerName, false)
            }

            Button {
                id: btnAgree
                enabled: false
                width: 100
                height: 30
                text: qsTr("Agree")
                style: CustomButton {}
                isDefault: true
                onClicked: {
                    controler.sendGameOfferReplay(controler.playerName, true)
                }
            }
        }
    }

    states: [
        State {
            name: "active"
            when: controler.currentView === "ShowGameOffer"
            PropertyChanges { target: showGameOffer; visible: true; }
        },
        State {
            name: "inactive"
            when: controler.currentView !== "ShowGameOffer"
            PropertyChanges { target: showGameOffer; visible: false; }
        }

    ]
}

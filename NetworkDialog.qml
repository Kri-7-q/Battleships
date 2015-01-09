import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Rectangle {
    width: parent.width * 0.8
    height: parent.height * 0.8
    anchors.centerIn: parent
    color: "goldenrod"
    border.color: "gray"
    border.width: 3
    radius: 20
    scale: window.scale
    property bool gameOfferAccepted: controler.hasGameOfferAccepted
    onGameOfferAcceptedChanged: state = "switch_game"

    Column {
        anchors.centerIn: parent
        spacing: 30

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 30

            Text {
                font.pixelSize: 20
                text: qsTr("offer a game")
            }

            Switch {
                id: gameOfferSwitch
                checked: true
                style: SwitchStyle {
                    groove: Rectangle {
                        implicitWidth: 100
                        implicitHeight: 35
                        radius: 3
                        border.color: control.activeFocus ? "darkblue" : "black"
                        border.width: 1
                        color: "gray"
                    }
                }
                onCheckedChanged: {
                    if (checked === false) {
                        // Server mode
                        controler.getNetworkInterfaceInfo()
                        networkAdapterCombo.model = controler.getNetworkInterfaceList()
                        var adapter = networkAdapterCombo.currentText
                        ipAddressCombo.model = controler.getIpAddressList(adapter)
                        ipAddressCombo.visible = true
                        ipAddressEdit.visible = false
                        networkAdapterCombo.enabled = true
                    } else {
                        networkAdapterCombo.enabled = false
                        ipAddressCombo.visible = false
                        ipAddressEdit.visible = true
                    }
                }
            }

            Text {
                font.pixelSize: 20
                text: qsTr("take a game")
            }
        } // END row

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 30

            Text {
                text: qsTr("Network interface")
            }

            ComboBox {
                id: networkAdapterCombo
                enabled: false
                width: 200
                onCurrentIndexChanged: {
                    var adapter = currentText
                    ipAddressCombo.model = controler.getIpAddressList(adapter)
                }
            }
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 30

            Text {
                text: qsTr("IP - Address")
            }

            // ComboBox in server mode
            ComboBox {
                id: ipAddressCombo
                visible: false
                width: 200
            }
            // TextEdit in client mode
            TextField {
                id: ipAddressEdit
                visible: true
                width: 200
            }
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 30

            Text {
                text: qsTr("Port")
            }

            TextField {
                id: portTextField
                width: 50
                horizontalAlignment: TextInput.AlignHCenter
                validator: IntValidator { bottom: 1; top: 65354; }
                placeholderText: qsTr("Port number")
            }
        }

        Button {
            text: (gameOfferSwitch.checked ? qsTr("Connect to Server") : qsTr("Start server"))
            width: 200
            height: 30
            style: CustomButton {}
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                if (gameOfferSwitch.checked === true) {
                    controler.initializeClientConnection(ipAddressEdit.text, portTextField.text)
                    networkDialog.state = "switch_gameOffer"
                } else {
                    controler.initializeServer(ipAddressCombo.currentText, portTextField.text)
                }
            }
        }


    } // END column

    states: [
        State {
            name: "active"
            when: controler.currentView === "NetworkDialog"
            PropertyChanges { target: networkDialog; visible: true; }
        },
        State {
            name: "inactive"
            when: controler.currentView !== "NetworkDialog"
            PropertyChanges { target: networkDialog; visible: false; }
        }
    ]
}

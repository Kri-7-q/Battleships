import QtQuick 2.0
import QtQuick.Controls 1.2

ApplicationWindow {
    width: 960
    height: 480
    visible: true
    title: "Battleships"

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem { text: qsTr("Close") }
        }
        Menu {
            title: qsTr("Mode")
            MenuItem { text: qsTr("Single Player") }
            MenuItem { text: qsTr("Multi Player") }
        }
    }

    // Draw background
    Rectangle {
        id: background
        anchors.fill: parent
        color: "lightblue"
    }

    //    SettingsDialog {
    //        state: "dialog_visible"
    //    }

    Item {
        id: gridModel
        property int columns: 10
        property int rows: 7
    }

    GameBoardView {
        id: foe
        name: "Foe"
    }

    GameBoardView {
        id: own
        name: "Christian"
        anchors.right: background.right
    }
}

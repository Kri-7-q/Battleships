import QtQuick 2.0

Rectangle {
    id: boardDelegate
    border.width: 1
    border.color: "black"
    state: "normal"
    states: [
        State {
            name: "normal"
            PropertyChanges { target: boardDelegate; color: "transparent" }
        },
        State {
            name: "hover"
            PropertyChanges { target: boardDelegate; color: "red" }
            PropertyChanges { target: boardDelegate; opacity: 0.4 }
        }
    ]

    MouseArea {
        id: cellMouseArea
        anchors.fill: parent
        hoverEnabled: enabled
        onEntered: parent.state = "hover"
        onExited: parent.state = "normal"
        preventStealing: true
    } // END mouse area
} // END delegate rectangle

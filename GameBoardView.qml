import QtQuick 2.0

// Game board with player name name as title.
Column {
    id: view
    property string name: "unknown"
    property var cursor: Qt.CrossCursor

    Rectangle {
        width: boardFrame.width
        height: boardFrame.headerHeight - 1
        color: "lightgreen"
        border.color: "black"
        border.width: 1
        Text {
            text: view.name
            font.bold: true
            anchors.centerIn: parent
        }
    }

    Rectangle {
        id: boardFrame
        property int margin: 1
        property int headerHeight: 30
        property int cellX: ((background.width - 20 - margin * 2) / 2) / gameBoardModel.columns
        property int cellY: (background.height - headerHeight - margin * 2) / gameBoardModel.rows
        property int cellSide: cellX > cellY ? cellY : cellX
        property int spacing: 1
        width: (cellSide + spacing) * gameBoardModel.columns + margin * 2 - spacing
        height: (cellSide + spacing) * gameBoardModel.rows + margin * 2 - spacing
        color: "black"
        Grid {
            id: board
            anchors.margins: boardFrame.margin
            anchors.fill: boardFrame
            columns: gameBoardModel.columns
            rows: gameBoardModel.rows
            spacing: boardFrame.spacing

            Repeater {
                model: gameBoardModel
                Rectangle {
                    id: boardDelegate
                    width: boardFrame.cellSide
                    height: boardFrame.cellSide
                    color: "lightblue"

                    MouseArea {
                        id: cellMouseArea
                        anchors.fill: parent
                        hoverEnabled: true
                        onEntered: cursorShape = view.cursor
                        onExited: cursorShape = Qt.ArrowCursor
                    }
                }
            }
        }
    }
}

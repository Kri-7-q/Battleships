import QtQuick 2.0

// Game board with player name name as title.
Column {
    id: view
    property string name: "unknown"

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
        property int cellX: ((background.width - 20 - margin * 2) / 2) / gridModel.columns
        property int cellY: (background.height - headerHeight - margin * 2) / gridModel.rows
        property int cellSide: cellX > cellY ? cellY : cellX
        property int spacing: 1
        width: (cellSide + spacing) * gridModel.columns + margin * 2 - spacing
        height: (cellSide + spacing) * gridModel.rows + margin * 2 - spacing
        color: "black"
        Grid {
            id: board
            anchors.margins: boardFrame.margin
            anchors.fill: boardFrame
            columns: gridModel.columns
            rows: gridModel.rows
            spacing: boardFrame.spacing

            Repeater {
                model: gridModel.columns * gridModel.rows
                Rectangle {
                    id: boardDelegate
                    width: boardFrame.cellSide
                    height: boardFrame.cellSide
                    color: "lightblue"
                }
            }
        }
    }
}

import QtQuick 2.0

// Game board with player name name as title.
Column {
    id: view
    property int availableWidth: 100
    property int availableHeight: 100
    property alias name: headerTitle.text
    readonly property alias cellSide: boardFrame.cellSide
    readonly property alias boardRect: boardFrame

    // Game board header (player name)
    Rectangle {
        width: boardFrame.width
        height: boardFrame.headerHeight - 1
        color: "lightgreen"
        border.color: "black"
        border.width: 1
        Text {
            id: headerTitle
            font.bold: true
            anchors.centerIn: parent
        }
    }

    // Black background as a frame (to get grid lines)
    Image {
        id: boardFrame
        property int headerHeight: 30
        property int cellApproximateX: view.availableWidth / gameBoardModel.columns
        property int cellApproximateY: (view.availableHeight - headerHeight) / gameBoardModel.rows
        property int cellSide: cellApproximateX > cellApproximateY ? cellApproximateY : cellApproximateX
        width: (cellSide + board.spacing) * gameBoardModel.columns - spacing
        height: (cellSide + board.spacing) * gameBoardModel.rows - spacing
        source: "qrc:resources/water_512.jpg"

        // Game board grid
        Grid {
            id: board
            anchors.fill: boardFrame
            columns: gameBoardModel.columns
            rows: gameBoardModel.rows
            spacing: -1
            property int pointerAngel: 0

            // Draw the fields
            Repeater {
                id: repeater
                model: gameBoardModel
                // Delegate to draw
                PlaceShipDelegate {
                    width: boardFrame.cellSide
                    height: boardFrame.cellSide
                }
            } // END repeater
        } // END grid
    } // END board frame
}

import QtQuick 2.0
import Models 1.0

// Game board with player name name as title.
Column {
    id: view
    property int availableWidth: 100
    property int availableHeight: 100
    property alias name: headerTitle.text
    readonly property alias cellSide: boardFrame.cellSide
    readonly property alias boardRect: boardFrame
    property Component delegate: Rectangle { width: cellSide; height: cellSide; color: "transparent" }
    property GameBoardModel model: GameBoardModel { columns: 5; rows: 5 }
    property int delegateAngel: 0
    property bool delgateMouseAreaEnabled: true

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
            font.pixelSize: 22 * window.scale
            anchors.centerIn: parent
        }
    }

    // Black background as a frame (to get grid lines)
    Image {
        id: boardFrame
        property int headerHeight: 30 * window.scale
        property int cellApproximateX: view.availableWidth / model.columns
        property int cellApproximateY: (view.availableHeight - headerHeight) / model.rows
        property int cellSide: cellApproximateX > cellApproximateY ? cellApproximateY : cellApproximateX
        width: (cellSide + boardGrid.spacing) * model.columns - spacing
        height: (cellSide + boardGrid.spacing) * model.rows - spacing
        source: "qrc:resources/water_512.jpg"

        // Game board grid
        Grid {
            id: boardGrid
            anchors.fill: boardFrame
            columns: view.model.columns
            rows: view.model.rows
            spacing: -1

            // Draw the fields
            Repeater {
                id: repeater
                model: view.model
                // Delegate to draw
                delegate: view.delegate
            } // END repeater
        } // END grid
    } // END board frame
}

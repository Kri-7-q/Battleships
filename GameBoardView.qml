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
        property int cellApproximateX: (view.availableWidth - 20) / gameBoardModel.columns
        property int cellApproximateY: (view.availableHeight - headerHeight) / gameBoardModel.rows
        property int cellSide: cellApproximateX > cellApproximateY ? cellApproximateY : cellApproximateX
        property int spacing: -1
        width: (cellSide + spacing) * gameBoardModel.columns - spacing
        height: (cellSide + spacing) * gameBoardModel.rows - spacing
        source: "file:/Users/Christian/Pictures/seichtesgewaesser_512.jpg"

        // Game board grid
        Grid {
            id: board
            anchors.fill: boardFrame
            columns: gameBoardModel.columns
            rows: gameBoardModel.rows
            spacing: boardFrame.spacing

            // Draw the fields
            Repeater {
                model: gameBoardModel
                // Delegate to draw
                Rectangle {
                    id: boardDelegate
                    width: boardFrame.cellSide
                    height: boardFrame.cellSide
                    color: "transparent"
                    border.color: "black"
                    border.width: 1

                    MouseArea {
                        id: cellMouseArea
                        anchors.fill: parent
                        hoverEnabled: enabled
                        onEntered: { parent.color = "gray"; parent.opacity = 0.3 }
                        onExited: { parent.color = "transparent"; parent.opacity = 1 }
                        preventStealing: true
                    } // END mouse area
                } // END delegate rectangle
            } // END repeater
        } // END grid
    } // END board frame
}

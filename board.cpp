#include "board.h"

/**
 * Contrutor
 * Constructs a game board with a given width and heigh.
 * @param width
 * @param heigh
 */
Board::Board(const quint8 width, const quint8 height) :
    width(width),
    height(height),
    emptyField(" ~ "),
    hiddenField(" x "),
    hiddenShip(" * ")
{
}

/**
 * Places a any ship to a given position.
 * @param ship          The ship to place.
 * @param x             The horizontaly position on game board.
 * @param y             The vertically position on game board.
 * @param d             The direction in which the ship is to place.
 * @return              True if ship was set to its position.
 */
bool Board::place(const Ship ship, const quint8 x, const quint8 y, const Direction d)
{

}

/**
 * Place a shoot at a given position.
 * @param x
 * @param y
 * @return          True if a ship was hidden.
 */
bool Board::shoot(const quint8 x, const quint8 y)
{

}

/**
 * Draw the game boeard on console.
 */
void Board::print()
{
    QString horzLine(width*4+1, '-');
    horzLine.append("\n");

    QString field;
    for (quint8 y=0; y<height; ++y) {
        printf(horzLine.toUtf8().data());
        for (quint8 x=0; x<width; ++x) {
            QPoint pt(x, y);
            field = getFieldState(pt);
            printf("|%s", field.toUtf8().data());
        }
        printf("|\n");
    }
    printf(horzLine.toUtf8().data() );
}

/**
 * Checks if a field contains a shot or a hidden ship.
 * @param point     The field (position) on the game board.
 * @return          A string which shows the state of field.
 */
QString Board::getFieldState(const QPoint point)
{
    for (Ship ship : shipList) {
        if (ship.isHidden(point)) {
            return hiddenShip;
        }
    }
    if (shotMap.value(point, false)) {
        return hiddenField;
    }

    return emptyField;
}

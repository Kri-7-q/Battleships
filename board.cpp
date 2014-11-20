#include "board.h"

/**
 * Contrutor
 * Constructs a game board with a given width and heigh.
 * @param width
 * @param heigh
 */
Board::Board(const quint8 width, const quint8 height) :
    mapRect(0, 0, width, height),
    emptyField(" ~ "),
    hiddenField(" x "),
    hiddenShip(" * ")
{
}

/**
 * Places a any ship to a given position.
 * Ship must be placed inside the game board.
 * Ship must not overlap another ship.
 * @param ship          The ship to place.
 * @param x             The horizontaly position on game board.
 * @param y             The vertically position on game board.
 * @param d             The direction in which the ship is to place.
 * @return              True if ship was set to its position.
 */
bool Board::place(const Ship ship, const quint8 x, const quint8 y, const Direction d)
{
    QRect shipRect = Ship::getShipPositionRect(QPoint(x, y), ship.getLength(), d);
    if (! mapRect.contains(shipRect)) {
        return false;
    }
    for (Ship placedShip : shipList) {
        if (placedShip.getPosition().intersects(shipRect)) {
            return false;
        }
    }
    Ship newShip(ship.getLength(), shipRect);
    shipList.append(newShip);

    return true;
}

/**
 * Place a shoot at a given position.
 * Return false if shot gone into the water.
 * Returns true if a ship was hidden at a undestroyed
 * position.
 * @param x
 * @param y
 * @return          True if a ship was hidden.
 */
bool Board::shoot(const quint8 x, const quint8 y)
{
    bool defaultValue = false;
    QPoint shotPosition(x, y);
    int fieldNumber = getFieldNumber(shotPosition);
    if (shotMap.value(fieldNumber, defaultValue)) {
        return false;
    }
    shotMap.insert(fieldNumber, true);
    for (Ship ship : shipList) {
        if (ship.isHidden(shotPosition)) {
            ship.addHit();
            return true;
        }
    }

    return false;
}

/**
 * Draw the game boeard on console.
 */
void Board::print()
{
    QString horzLine(mapRect.width()*4+1, '-');
    horzLine.append("\n");

    QString field;
    for (quint8 y=0; y<mapRect.height(); ++y) {
        printf(horzLine.toUtf8().data());
        for (quint8 x=0; x<mapRect.width(); ++x) {
            QPoint pt(x, y);
            field = getFieldState(pt);
            printf("|%s", field.toUtf8().data());
        }
        printf("|\n");
    }
    printf( horzLine.toUtf8().data() );
}

/**
 * Checks if a field contains a shot or a hidden ship.
 * @param point     The field (position) on the game board.
 * @return          A string which shows the state of field.
 */
QString Board::getFieldState(const QPoint &point)
{
    for (Ship ship : shipList) {
        if (ship.isHidden(point)) {
            return hiddenShip;
        }
    }
    bool defaultValue = false;
    int fieldNumber = getFieldNumber(point);
    if (shotMap.value(fieldNumber, defaultValue)) {
        return hiddenField;
    }

    return emptyField;
}

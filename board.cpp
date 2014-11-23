#include "board.h"

/**
 * Contrutor
 * Constructs a game board with a given width and heigh.
 * @param width
 * @param heigh
 */
Board::Board(const quint8 width, const quint8 height) :
    boardRect(0, 0, width, height),
    emptyField(" ~ "),
    hiddenField(" o "),
    hiddenShip(" X ")
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
    if (! boardRect.contains(shipRect)) {
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
 * Marks a new hit on a ship.
 * It does not test if shoot is within game board.
 * @param x
 * @param y
 * @return          True if ship was hidden.
 */
bool Board::shoot(const quint8 x, const quint8 y)
{
    QPoint shotPosition(x, y);
    bool isHit = shotMayHitShip(shotPosition);
    int fieldNumber = getFieldNumber(shotPosition);
    shotMap.insert(fieldNumber, true);

    return isHit;
}

/**
 * Draw the game boeard on console.
 */
void Board::print()
{
    QString horzLine(boardRect.width()*4+1, '-');
    horzLine.prepend("  ").append("\n");

    printf("  ");
    for (quint8 x=0; x<boardRect.width(); ++x) {
        printf("  %i ", x);
    }
    printf("\n");
    QString field;
    for (quint8 y=0; y<boardRect.height(); ++y) {
        printf(horzLine.toUtf8().data());
        printf("%i ", y);
        for (quint8 x=0; x<boardRect.width(); ++x) {
            QPoint pt(x, y);
            field = getFieldState(pt);
            printf("|%s", field.toUtf8().data());
        }
        printf("|\n");
    }
    printf( horzLine.toUtf8().data() );
}

/**
 * Check if there is any ship left.
 * @return      False if all ships are destroyed.
 */
bool Board::hasUndestroyedShip()
{
    for (Ship ship : shipList) {
        if (! ship.isDestroyed()) {
            return true;
        }
    }

    return false;
}

/**
 * Checks if a field contains a shot or a hidden ship.
 * @param point     The field (position) on the game board.
 * @return          A string which shows the state of field.
 */
QString Board::getFieldState(const QPoint &point)
{
    bool defaultValue = false;
    int fieldNumber = getFieldNumber(point);
    bool isFieldHidden = shotMap.value(fieldNumber, defaultValue);
    for (Ship ship : shipList) {
        if (ship.isOnShip(point) && isFieldHidden) {
            return hiddenShip;
        }
    }
    if (isFieldHidden) {
        return hiddenField;
    }

    return emptyField;
}

/**
 * Mark a ship hidden if shot was a hit.
 * @param shotPosition
 */
bool Board::shotMayHitShip(QPoint shotPosition)
{
    bool defaultValue = false;
    int fieldNumber = getFieldNumber(shotPosition);
    bool wasHiddenBefore = shotMap.value(fieldNumber, defaultValue);
    if (! wasHiddenBefore) {
        for (Ship &ship : shipList) {
            if (ship.isOnShip(shotPosition)) {
                ship.addHit();
                return true;
            }
        }
    }

    return false;
}

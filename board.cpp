#include "board.h"

/**
 * Standard constructor
 */
Board::Board(QObject *parent) :
    GameBoardModel(parent)
{
}

/**
 * Contrutor
 * Constructs a game board with a given width and heigh.
 * @param width
 * @param heigh
 */
Board::Board(const quint8 width, const quint8 height, QObject *parent) :
    GameBoardModel(parent),
    emptyFieldString(" ~ "),
    hiddenFieldString(" o "),
    hiddenShipString(" X ")
{
    setColumns(width);
    setRows(height);
}

/**
 * Places any ship to a given position.
 * Ship must be placed inside the game board.
 * Ship must not overlap another ship.
 * @param ship          The ship to place.
 * @param x             The horizontaly position on game board.
 * @param y             The vertically position on game board.
 * @param d             The direction in which the ship is to place.
 * @return              True if ship was set to its position.
 */
bool Board::place(Ship ship, const quint8 x, const quint8 y, const Ship::Direction d)
{
    QRect shipRect = Ship::getShipPositionRect(x, y, ship.length(), d);
    if (! gameBoardRect().contains(shipRect)) {
        return false;
    }
    ship.setShipsPosition(shipRect);
    int topLeft = getFieldNumber(shipRect.topLeft());
    int bottomRight = getFieldNumber(shipRect.bottomRight());

    return placeShipToGameBoard(ship, topLeft, bottomRight);
}

/**
 * Place a shoot at a given position.
 * Adds a hit on a ship if shot hit a ship.
 * It does not test if shoot is within game board.
 * @param x
 * @param y
 * @return          True if ship was hidden.
 */
bool Board::shoot(const quint8 x, const quint8 y)
{
    int fieldNumber = getFieldNumber(x, y);
    FieldState state = (FieldState)data(index(fieldNumber), Qt::DisplayRole).toInt();
    if (state != GameBoardModel::EmptyField) {
        return false;
    }
    bool isHit = data(index(fieldNumber), ShipAtPositionRole).toBool();
    if (isHit) {
        setData(index(fieldNumber), QVariant(), ModifyShipHealthRole);
        setData(index(fieldNumber), QVariant(HiddenShip), ModifyFieldStateRole);
    } else {
        setData(index(fieldNumber), QVariant(HiddenField), ModifyFieldStateRole);
    }

    return isHit;
}

/**
 * Draw the game boeard on console.
 */
void Board::print()
{
    QString horzLine(columns()*4+1, '-');
    horzLine.prepend("  ").append("\n");

    printf("  ");
    for (quint8 x=0; x<columns(); ++x) {
        printf("  %i ", x);
    }
    printf("\n");
    QString field;
    for (quint8 y=0; y<rows(); ++y) {
        printf(horzLine.toUtf8().data());
        printf("%i ", y);
        for (quint8 x=0; x<columns(); ++x) {
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
    return data(index(0), HasUndestroiedShipRole).toBool();
}

/**
 * Checks if a field contains a shot or a hidden ship.
 * @param point     The field (position) on the game board.
 * @return          A string which shows the state of field.
 */
QString Board::getFieldState(const QPoint &point) const
{
    int fieldNumber = getFieldNumber(point);
    FieldState state = (FieldState)data(index(fieldNumber), Qt::DisplayRole).toInt();
    switch (state) {
    case EmptyField:
        return emptyFieldString;
        break;
    case HiddenField:
        return hiddenFieldString;
        break;
    case HiddenShip:
        return hiddenShipString;
        break;
    default:
        break;
    }

    return QString();
}

/**
 * SLOT
 * Places a ship on the game board if posible with the given values.
 * @param length        The ships length (size).
 * @param name          The ships name. (Air Carier, Destroyer, ...)
 * @param index         The fields index.
 * @param angel         An angel value where north is 0 and Right 90 ...
 * @return              True if ship was succesfully placed on the board.
 */
bool Board::placeShip(const int length, const QString name, const int index, const int angel)
{
    QPoint position = getPointObject(index);
    Ship::Direction direction = Ship::getDirectionFromAngel(angel);

    return place(Ship(length, name), position.x(), position.y(), direction);
}

/**
 * SLOT
 * Takes a shoot from GUI.
 * @param index         The index of game board field.
 * @return              True if a ship was hidden.
 */
bool Board::shootAt(const int index)
{
    QPoint point = getPointObject(index);

    return shoot(point.x(), point.y());
}

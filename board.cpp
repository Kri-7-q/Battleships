#include "board.h"

/**
 * Standard constructor
 */
Board::Board()
{

}

/**
 * Contrutor
 * Constructs a game board with a given width and heigh.
 * @param width
 * @param heigh
 */
Board::Board(const quint8 width, const quint8 height) :
    emptyFieldString(" ~ "),
    hiddenFieldString(" o "),
    hiddenShipString(" X ")
{
    model.setColumns(width);
    model.setRows(height);
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
bool Board::place(const Ship ship, const quint8 x, const quint8 y, const Ship::Direction d)
{
    QRect shipRect = Ship::getShipPositionRect(QPoint(x, y), ship.length(), d);
    if (! model.gameBoardRect().contains(shipRect)) {
        return false;
    }
    Ship newShip(ship.length(), shipRect);

    return model.placeShip(newShip);
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
    GameBoardModel::FieldState state = (GameBoardModel::FieldState)model.data(model.index(fieldNumber), Qt::DisplayRole).toInt();
    if (state != GameBoardModel::emptyField) {
        return false;
    }
    bool isHit = model.data(model.index(fieldNumber), GameBoardModel::ShipAtPositionRole).toBool();
    if (isHit) {
        model.setData(model.index(y, x), QVariant(), GameBoardModel::ModifyShipHealthRole);
        model.setData(model.index(fieldNumber), QVariant(GameBoardModel::hiddenShip), GameBoardModel::ModifyFieldStateRole);
    } else {
        model.setData(model.index(fieldNumber), QVariant(GameBoardModel::hiddenField), GameBoardModel::ModifyFieldStateRole);
    }

    return isHit;
}

/**
 * Draw the game boeard on console.
 */
void Board::print()
{
    QString horzLine(model.columns()*4+1, '-');
    horzLine.prepend("  ").append("\n");

    printf("  ");
    for (quint8 x=0; x<model.columns(); ++x) {
        printf("  %i ", x);
    }
    printf("\n");
    QString field;
    for (quint8 y=0; y<model.rows(); ++y) {
        printf(horzLine.toUtf8().data());
        printf("%i ", y);
        for (quint8 x=0; x<model.columns(); ++x) {
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
    return model.data(model.index(0), GameBoardModel::HasUndestroiedShipRole).toBool();
}

/**
 * Checks if a field contains a shot or a hidden ship.
 * @param point     The field (position) on the game board.
 * @return          A string which shows the state of field.
 */
QString Board::getFieldState(const QPoint &point) const
{
    int fieldNumber = getFieldNumber(point);
    GameBoardModel::FieldState state = (GameBoardModel::FieldState)model.data(model.index(fieldNumber), Qt::DisplayRole).toInt();
    switch (state) {
    case GameBoardModel::emptyField:
        return emptyFieldString;
        break;
    case GameBoardModel::hiddenField:
        return hiddenFieldString;
        break;
    case GameBoardModel::hiddenShip:
        return hiddenShipString;
        break;
    default:
        break;
    }

    return QString();
}

/**
 * Get a point object from a field number.
 * The field number is counted in a grid from left to rigth
 * and in this manner from top to the buttom row.
 * @param fieldNumber       Field number counted from top-left corner.
 * @return                  A point object.
 */
QPoint Board::getPointObject(const int fieldNumber) const
{
    QPoint point;
    point.setX(fieldNumber % model.columns());
    point.setY(fieldNumber / model.columns());

    return point;
}

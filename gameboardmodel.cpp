#include "gameboardmodel.h"

/**
 * Constructor
 * @param parent
 */
GameBoardModel::GameBoardModel(QObject *parent) :
    QAbstractListModel(parent),
    m_boardRect(0,0,0,0)
{
}

/**
 * Property setter
 * Set game board width.
 * @param width
 */
void GameBoardModel::setColumns(const int width)
{
    if (width != m_boardRect.width()) {
        m_boardRect.setWidth(width);
        emit columnsChanged();
    }
}

/**
 * Property setter
 * Set game board height.
 * @param height
 */
void GameBoardModel::setRows(const int height)
{
    if (height != m_boardRect.height()) {
        m_boardRect.setHeight(height);
        emit rowsChanged();
    }
}

/**
 * Try to place a new Ship on the game board.
 * It must not overlap any other ship.
 * @param newShip
 * @return              True if ship was placed.
 */
bool GameBoardModel::placeShipToGameBoard(const Ship &newShip, int topLeft, int bottomRight)
{
    for (Ship ship : m_shipList) {
        if (ship.position().intersects(newShip.position())) {
            return false;
        }
    }
    m_shipList.append(newShip);
    emit dataChanged(index(topLeft), index(bottomRight));

    return true;
}

/**
 * Get game board field count.
 * This is a list model. All game board fields are listed.
 * They are counted from top-left corner to bottom-right corner.
 * @param parent
 * @return          The number of fields on game board.
 */
int GameBoardModel::rowCount(const QModelIndex &parent) const
{
    return m_boardRect.width() * m_boardRect.height();
}

/**
 * Qt::DisplayRole
 * Get the state of a game board field. There are three states:
 * emptyFiled, hiddenField and hiddenShip.
 * ShipRole
 * Search for a Ship object at the given position.
 * Position should be given in the index value.
 * Returns true if a ship is at this position.
 * ...
 * ............................................
 * ...
 * @param index     The field of game board.
 * @param role
 * @return          The content depends on the request (role).
 */
QVariant GameBoardModel::data(const QModelIndex &index, int role) const
{
    QVariant value;
    switch (role) {
    case Qt::DisplayRole:
        value = QVariant(m_fieldStateList.value(index.row(), emptyField));
        break;
    case ShipAtPositionRole:
        value = QVariant(false);
        for (const Ship ship : m_shipList) {
            if (ship.isOnShip(index.column(), index.row())) {
                value = QVariant(true);
                break;
            }
        }
        break;
    case HasUndestroiedShipRole:
        value = QVariant(false);
        for (const Ship ship : m_shipList) {
            if (! ship.isDestroyed()) {
                value = QVariant(true);
            }
        }
        break;
    case PlaceShipsRole: {
        QPoint point(index.row() % m_boardRect.width(), index.row() / m_boardRect.width());
        for (const Ship ship : m_shipList) {
            if (ship.isOnShip(point)) {
                return QVariant(true);
            }
        }
        value = QVariant(false);
        break;
    }
    default:
        break;
    }

    return value;
}

/**
 * Modify model data.
 * ModifyFieldStateRole:
 * This modifies the state of a field. A field could be emptyField,
 * hiddenField or hiddenShip.
 * ModifyShipHealthRole:
 * Ships hit counter is incremented if ship was hidden by a shot.
 * @param index
 * @param value
 * @param role
 * @return
 */
bool GameBoardModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    switch (role) {
    case ModifyFieldStateRole: {
        FieldState state = (FieldState)value.toInt();
        m_fieldStateList.insert(index.row(), state);
        emit dataChanged(index, index);
        break;
    }
    case ModifyShipHealthRole:
        for (Ship &ship : m_shipList) {
            if (ship.position().contains(index.column(), index.row())) {
                ship.addHit();
                break;
            }
        }
        break;
    default:
        break;
    }

    return true;
}

/**
 * Export model roles to QML.
 * @return roles        A QHash object containig some model role for QML.
 */
QHash<int, QByteArray> GameBoardModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::DisplayRole] = "display";
    roles[PlaceShipsRole] = "placeShips";

    return roles;
}

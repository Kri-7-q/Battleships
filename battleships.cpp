#include "battleships.h"

/**
 * Construtor
 * Constructs a Battleship object.
 */
Battleships::Battleships(QObject *parent) :
    QObject(parent),
    m_shotsFired(0)
{
    m_defaultShips.insert("Aircraft carrier", 5);
    m_defaultShips.insert("Battleship", 4);
    m_defaultShips.insert("Submarine", 3);
    m_defaultShips.insert("Cruiser", 3);
    m_defaultShips.insert("Destroyer", 2);
}

// Getter
QString Battleships::playerName() const
{
    return m_playerName;
}

// Setter
void Battleships::setPlayerName(const QString name)
{
    m_playerName = name;
}

/**
 * Takes a string with komma seperated integr values for coordinates
 * and a letter to indicate ships direction.
 * These values are put into a ShipPosition object.
 * @param input                 A string with komma seperated values.
 * @return position             A ShipPosition object containing the values.
 */
ShipPosition Battleships::getShipPosition(const QString input)
{
    ShipPosition position = {-1, -1, Up};
    QStringList value = input.split(',');
    if (value.size() < 3) {
        return position;
    }
    bool ok;
    int x = value[0].toInt(&ok);
    position.x = (ok) ? x : -1 ;
    int y = value[1].toInt(&ok);
    position.y = (ok) ? y : -1 ;
    char *direction = value[2].toUtf8().data();
    switch (direction[0]) {
    case 'l':
        position.direction = Left;
        break;
    case 'r':
        position.direction = Right;
        break;
    case 'u':
        position.direction = Up;
        break;
    case 'd':
        position.direction = Down;
        break;
    default:
        position.direction = Down;
        break;
    }

    return position;
}

/**
 * Creates a random position and direction for a ship.
 * @param boardSize     The size of game board.
 * @return              A ShipPosition object with position and direction.
 */
ShipPosition Battleships::getRandomShipPosition(const QSize boardSize)
{
    int x = qrand() % boardSize.width();
    int y = qrand() % boardSize.height();
    Direction dir = getRandomDirection();
    ShipPosition position = { x, y, dir };

    return position;
}

/**
 * Get a random direction value.
 * @return      The ships direction;
 */
Direction Battleships::getRandomDirection()
{
    Direction dir;
    int random = qrand() % 4;
    switch (random) {
    case 0:
        dir = Right;
        break;
    case 1:
        dir = Left;
        break;
    case 2:
        dir = Up;
        break;
    case 3:
        dir = Down;
        break;
    default:
        dir = Right;
        break;
    }

    return dir;
}

/**
 * Takes a string with komma seperated integer values.
 * These values are put into a QPoint object.
 * @param input     A string with to integer values komma seperated.
 * @return          A QPoint object containing these values. Or (-1,-1) if string was invalid.
 */
QPoint Battleships::getPointObject(const QString input)
{
    QStringList value = input.split(',');
    if (value.size() < 2) {
        return QPoint(-1, -1);
    }
    QPoint point;
    bool ok;
    int x = value[0].toInt(&ok);
    point.setX( (ok) ? x : -1 ) ;
    int y = value[1].toInt(&ok);
    point.setY( (ok) ? y : -1 );

    return point;
}

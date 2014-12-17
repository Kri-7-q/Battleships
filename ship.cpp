#include "ship.h"


/**
 * Constructor
 * Constructs a battleship.
 * @param length        The size (length) of the battleship.
 */

Ship::Ship(const quint8 length, QString name) :
    m_length(length),
    hits(0),
    m_position(0,0,0,0),
    m_name(name)
{
}

/**
 * Constructor
 * Constructs a battleship with its position on map.
 * @param length        The ships size (lenght).
 * @param position      The position on the map.
 */
Ship::Ship(const quint8 length, const QRect position, QString name) :
    m_length(length),
    m_position(position),
    hits(0),
    m_name(name)
{

}

/**
 * Ship is hidden by a shot.
 */
void Ship::addHit()
{
    ++hits;
}

/**
 * STATIC
 * Creates a rectangle of the ships position in the map.
 * @param point             The point which the user has chosen.
 * @param length            The length of the ship.
 * @param direction         The direction in which the ship is laid.
 * @return rect             A QRect with the ships position in the map.
 */
QRect Ship::getShipPositionRect(const int x, const int y, const quint8 length, const Direction direction)
{
    const int l = length - 1;
    QRect rect;
    switch (direction) {
    case Up:
        rect.setCoords(x, y-l, x, y);
        break;
    case Down:
        rect.setCoords(x, y, x, y+l);
        break;
    case Left:
        rect.setCoords(x-l, y, x, y);
        break;
    case Right:
        rect.setCoords(x, y, x+l, y);
        break;
    default:
        break;
    }

    return rect;
}

/**
 * Get a direction from an angel value.
 * @param angel
 * @return          A Direction value.
 */
Ship::Direction Ship::getDirectionFromAngel(int angel)
{
    switch (angel) {
    case 0:
        return Up;
        break;
    case 90:
        return Right;
        break;
    case 180:
        return Down;
        break;
    case 270:
        return Left;
        break;
    default:
        return Up;
        break;
    }

    return Up;
}

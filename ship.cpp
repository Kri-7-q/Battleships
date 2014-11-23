#include "ship.h"

/**
 * Constructor
 * Constructs a battleship.
 * @param length        The size (length) of the battleship.
 */
Ship::Ship(const quint8 length) :
    length(length),
    hits(0)
{
}

/**
 * Constructor
 * Constructs a battleship with its position on map.
 * @param length        The ships size (lenght).
 * @param position      The position on the map.
 */
Ship::Ship(const quint8 length, const QRect position) :
    length(length),
    position(position),
    hits(0)
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
QRect Ship::getShipPositionRect(const QPoint point, const quint8 length, const Direction direction)
{
    const int l = length - 1;
    QRect rect;
    switch (direction) {
    case Up:
        rect.setCoords(point.x(), point.y()-l, point.x(), point.y());
        break;
    case Down:
        rect.setCoords(point.x(), point.y(), point.x(), point.y()+l);
        break;
    case Left:
        rect.setCoords(point.x()-l, point.y(), point.x(), point.y());
        break;
    case Right:
        rect.setCoords(point.x(), point.y(), point.x()+l, point.y());
        break;
    default:
        break;
    }

    return rect;
}

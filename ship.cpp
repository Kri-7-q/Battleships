#include "ship.h"

/**
 * Constructor
 * Constructs a battleship.
 * @param length        The size (length) of the battleship.
 * @param description   A description (type) of a battleship.
 */
Ship::Ship(const quint8 length, const QString description, const QRect position) :
    length(length),
    description(description),
    position(position)
{
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
    QRect rect;
    switch (direction) {
    case Up:
        rect.setCoords(point.x(), point.y()-length, point.x(), point.y());
        break;
    case Down:
        rect.setCoords(point.x(), point.y(), point.x(), point.y()+length);
        break;
    case Left:
        rect.setCoords(point.x()-length, point.y(), point.x(), point.y());
        break;
    case Right:
        rect.setCoords(point.x(), point.y(), point.x()+length, point.y());
        break;
    default:
        break;
    }

    return rect;
}

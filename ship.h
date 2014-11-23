/**
  * Class SHip
  * ----------------
  * Represents a Ship in this game.
  * A ship knows its position as a QRect which keeps
  * the position on the game board.
  * You can ask a ship if it was hidden by the shot.
  * It has a hit counter and knows when it is destroyed.
  */
#ifndef SHIP_H
#define SHIP_H
#include <QString>
#include <QRect>
#include "Utilities.h"

class Ship
{
public:
    Ship(const quint8 length);
    Ship(const quint8 length, const QRect position);

protected:
    quint8 hits;
    quint8 length;
    QRect position;

public:
    bool isOnShip(QPoint pt)            { return position.contains(pt); }
    quint8 getLength() const            { return length; }
    QRect getPosition() const           { return position; }
    bool isDestroyed() const            { return hits >= length; }
    void addHit();

    // Static members
    static QRect getShipPositionRect(const QPoint point, const quint8 length, const Direction direction);

};

#endif // SHIP_H

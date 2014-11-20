#ifndef SHIP_H
#define SHIP_H
#include <QString>
#include <QPoint>
#include <QRect>
#include "EnumType.h"

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
    bool isHidden(QPoint pt)            { return position.contains(pt); }
    quint8 getLength() const            { return length; }
    QRect getPosition() const           { return position; }
    bool isDestroyed() const            { return hits == length; }
    void addHit()                       { ++hits; }

    // Static members
    static QRect getShipPositionRect(const QPoint point, const quint8 length, const Direction direction);

};

#endif // SHIP_H

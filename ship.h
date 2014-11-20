#ifndef SHIP_H
#define SHIP_H
#include <QString>
#include <QPoint>
#include <QRect>
#include "EnumType.h"

class Ship
{
public:
    Ship(const quint8 length, const QString description, const QRect position);

protected:
    const quint8 length;
    const QString description;
    const QRect position;

public:
    bool isHidden(QPoint pt)            { return position.contains(pt); }

    static QRect getShipPositionRect(const QPoint point, const quint8 length, const Direction direction);
};

#endif // SHIP_H

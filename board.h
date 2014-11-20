#ifndef BOARD_H
#define BOARD_H
#include <QList>
#include <QPoint>
#include <QHash>
#include <QRect>
#include "ship.h"
#include "EnumType.h"

class Board
{
public:
    Board(const quint8 width, const quint8 height);

protected:
    const QString emptyField;
    const QString hiddenField;
    const QString hiddenShip;
    QRect mapRect;
    QList<Ship> shipList;
    QHash<int, bool> shotMap;

public:
    // Methods
    bool place(const Ship ship, const quint8 x, const quint8 y, const Direction d);
    bool shoot(const quint8 x, const quint8 y);
    void print();

protected:
    QString getFieldState(const QPoint &point);
    int getFieldNumber(const QPoint &point)        { return point.y() * mapRect.width() + point.x(); }
};

#endif // BOARD_H

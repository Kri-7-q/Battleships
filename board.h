#ifndef BOARD_H
#define BOARD_H
#include <QList>
#include <QPoint>
#include <QHash>
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
    const quint8 width;
    const quint8 height;
    QList<Ship> shipList;
    QHash<QPoint, bool> shotMap;

public:
    // Methods
    bool place(const Ship ship, const quint8 x, const quint8 y, const Direction d);
    bool shoot(const quint8 x, const quint8 y);
    void print();

protected:
    QString getFieldState(const QPoint point);
};

#endif // BOARD_H

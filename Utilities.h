#ifndef ENUMTYPE_H
#define ENUMTYPE_H
#include <QtGlobal>

enum Direction { Right, Left, Up, Down };


struct ShipPosition {
    quint8 x;
    quint8 y;
    Direction direction;
};

#endif // ENUMTYPE_H

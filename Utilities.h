#ifndef ENUMTYPE_H
#define ENUMTYPE_H
#include <QtGlobal>
#include <Qt>

enum Direction { Right, Left, Up, Down };

enum FieldState { emptyField, hiddenField, hiddenShip };

struct ShipPosition {
    quint8 x;
    quint8 y;
    Direction direction;
};

// Model role
const int ShipAtPositionRole = Qt::UserRole;
const int HasUndestroiedShipRole = Qt::UserRole + 1;
const int ModifyFieldStateRole = Qt::UserRole + 2;
const int ModifyShipHealthRole = Qt::UserRole + 3;

#endif // ENUMTYPE_H

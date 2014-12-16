#ifndef ENUMTYPE_H
#define ENUMTYPE_H
#include "ship.h"

struct ShipPosition {
    int x;
    int y;
    Ship::Direction direction;
};


#endif // ENUMTYPE_H

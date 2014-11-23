/**
  * Class Battleship
  * -------------------
  * Is the main class. It has the players name and
  * a shot counter of all shots taken.
  * It also keeps a default list of ships. Its a QHash table
  * with the ships name as key and the ships length as value.
  * The class can create a random position and direction for
  * a ship. And it converts input strings into usable values.
  */
#ifndef BATTLESHIPS_H
#define BATTLESHIPS_H
#include <QStringList>
#include <QHash>
#include <QSize>
#include <QPoint>
#include "Utilities.h"


class Battleships
{
public:
    Battleships();

    QString getPlayerName() const;
    quint16 getShotsFired()                     { return shotsFired; }
    void setPlayerName(const QString name);
    QHash<QString,int> getDefaultShips()        { return defaultShips; }
    ShipPosition getShipPosition(const QString input);
    ShipPosition getRandomShipPosition(const QSize boardSize);
    void addShoot()                             { ++shotsFired; }
    QPoint getPointObject(const QString input);

protected:
    QString playerName;
    quint16 shotsFired;
    QHash<QString, int> defaultShips;

    // Methods
    Direction getRandomDirection();
};

#endif // BATTLESHIPS_H

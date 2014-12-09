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
#include <QObject>
#include "Utilities.h"


class Battleships : public QObject
{
    Q_OBJECT
public:
    explicit Battleships(QObject *parent = 0);

    QString playerName() const;
    quint16 shotsFired()                     { return m_shotsFired; }
    void setPlayerName(const QString name);
    QHash<QString,int> defaultShips()        { return m_defaultShips; }
    ShipPosition getShipPosition(const QString input);
    ShipPosition getRandomShipPosition(const QSize boardSize);
    void addShoot()                             { ++m_shotsFired; }
    QPoint getPointObject(const QString input);

private:
    QString m_playerName;
    quint16 m_shotsFired;
    QHash<QString, int> m_defaultShips;

    // Methods
    Direction getRandomDirection();
};

#endif // BATTLESHIPS_H

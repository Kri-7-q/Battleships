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

class Ship
{
public:
    Ship(const quint8 length);
    Ship(const quint8 length, const QRect m_position);

    enum Direction { Right, Left, Up, Down };

protected:
    quint8 hits;
    quint8 m_length;
    QRect m_position;

public:
    bool isOnShip(const QPoint &pt) const               { return m_position.contains(pt); }
    bool isOnShip(const int x, const int y) const       { return m_position.contains(x, y); }
    quint8 length() const                               { return m_length; }
    QRect position() const                              { return m_position; }
    bool isDestroyed() const                            { return hits >= m_length; }
    void addHit();

    // Static members
    static QRect getShipPositionRect(const QPoint point, const quint8 m_length, const Direction direction);

};

#endif // SHIP_H

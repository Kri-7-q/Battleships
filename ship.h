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
    Ship(const quint8 length, QString name = QString("unknown"));
    Ship(const quint8 length, const QRect m_position, QString name = QString("unknown"));

    enum Direction { Right, Left, Up, Down };

protected:
    quint8 hits;
    quint8 m_length;
    QRect m_position;
    QString m_name;

public:
    bool isOnShip(const QPoint &pt) const               { return m_position.contains(pt); }
    bool isOnShip(const int x, const int y) const       { return m_position.contains(x, y); }
    quint8 length() const                               { return m_length; }
    QRect position() const                              { return m_position; }
    bool isDestroyed() const                            { return hits >= m_length; }
    void addHit();
    void setShipsPosition(const QRect positionRect)     { m_position = positionRect; }

    // Static members
    static QRect getShipPositionRect(const int x, const int y, const quint8 m_length, const Direction direction);
    static Direction getDirectionFromAngel(int angel);

};

#endif // SHIP_H

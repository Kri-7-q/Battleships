/**
  * Class Board
  * -----------------
  * Represents the Battleship game board.
  * If consists of a QRect and contains a list of ships.
  * The game board takes the shots which the player has
  * taken. These shot are stored in a QHash table.
  * The game board knows if a ship was hidden and if
  * there are any undestroyed ships left.
  * The ships are placed on this game board and stored
  * in a QList.
  */
#ifndef BOARD_H
#define BOARD_H
#include <QList>
#include <QTextStream>
#include <QHash>
#include <QRect>
#include "ship.h"
#include "Utilities.h"

class Board
{
public:
    Board(const quint8 width, const quint8 height);

protected:
    const QString emptyField;
    const QString hiddenField;
    const QString hiddenShip;
    QRect boardRect;
    QList<Ship> shipList;
    QHash<int, bool> shotMap;

public:
    // Methods
    bool place(const Ship ship, const quint8 x, const quint8 y, const Direction d);
    bool shoot(const quint8 x, const quint8 y);
    void print();
    QSize getGameBoardSize()                    { return boardRect.size(); }
    bool hasUndestroyedShip();
    bool isWithinGameBoard(const QPoint pt)         { return boardRect.contains(pt); }

protected:
    QString getFieldState(const QPoint &point);
    int getFieldNumber(const QPoint &point)        { return point.y() * boardRect.width() + point.x(); }
    bool shotMayHitShip(QPoint shotPosition);
};

#endif // BOARD_H

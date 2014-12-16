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
#include "gameboardmodel.h"

class Board
{
public:
    Board();
    Board(const quint8 width, const quint8 height);

protected:
    const QString emptyFieldString;
    const QString hiddenFieldString;
    const QString hiddenShipString;
    GameBoardModel model;

public:
    // Methods
    bool place(const Ship ship, const quint8 x, const quint8 y, const Ship::Direction d);
    bool shoot(const quint8 x, const quint8 y);
    void print();
    QSize getGameBoardSize()                    { return model.gameBoardRect().size(); }
    bool hasUndestroyedShip();
    bool isWithinGameBoard(const QPoint &pt)         { return model.gameBoardRect().contains(pt); }
    GameBoardModel* getModel()                       { return &model; }

private:
    QString getFieldState(const QPoint &point) const;
    int getFieldNumber(const QPoint &point) const               { return point.y() * model.columns() + point.x(); }
    int getFieldNumber(const quint8 x, const quint8 y) const    { return y * model.columns() + x; }
    QPoint getPointObject(const int fieldNumber) const;
};
#endif // BOARD_H

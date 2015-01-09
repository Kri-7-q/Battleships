/**
  * Class Board
  * --------------------------------------------------
  * Represents the Battleship game board.
  * Inherits:   Class GameBoardModel
  * ---------------------------------------------------
  * It consists of a QRect and contains a list of ships.
  * The game board takes the shots which the player has
  * taken. These shot are stored in a QHash table.
  * The game board knows if a ship was hidden and if
  * there are any undestroyed ships left.
  * The ships are placed on this game board and stored
  * in a QList.
  */
#ifndef BOARD_H
#define BOARD_H
# include "gameboardmodel.h"

class Board : public GameBoardModel
{
    Q_OBJECT
public:
    explicit Board(QObject *parent = 0);
    explicit Board(const quint8 width, const quint8 height, QObject *parent = 0);

private:
    const QString emptyFieldString;
    const QString hiddenFieldString;
    const QString hiddenShipString;

public:
    // Methods
    bool place(Ship ship, const quint8 x, const quint8 y, const Ship::Direction d);
    const Ship* shoot(const quint8 x, const quint8 y);
    void print();
    QSize getGameBoardSize()                    { return gameBoardRect().size(); }
    bool hasUndestroyedShip();
    bool isWithinGameBoard(const QPoint &pt)         { return gameBoardRect().contains(pt); }
    int getFieldNumber(const QPoint &point) const               { return point.y() * columns() + point.x(); }
    int getFieldNumber(const quint8 x, const quint8 y) const    { return y * columns() + x; }

private:
    QString getFieldState(const QPoint &point) const;

signals:

public slots:
    bool placeShip(const int length, const QString name, const int index, const int angel);
    const Ship* shootAt(const int index);
};

#endif // BOARD_H

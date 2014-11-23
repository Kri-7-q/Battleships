/**
  * Class ConsoleInterface
  * -----------------------------
  * A class to get player input and print
  * results to the console.
  * Its to interact with the player.
  */
#ifndef CONSOLEINTERFACE_H
#define CONSOLEINTERFACE_H
#include <QStringList>
#include <QTextStream>
#include <QSize>
#include <QHash>
#include "board.h"

class ConsoleInterface
{
public:
    ConsoleInterface();

    QTextStream cin;
    QTextStream cout;
    QTextStream err;

    // Methods
    QString getPlayerName();
    QSize getBoardSize();
    QString getPositionForShip(const QString description);
    void drawGameBoard(Board &gameBoard);
    QHash<QString, int> getCustomShips();
    QString getShot();
    void printText(const QString text)          { cout << text << endl; }
    bool wantCustomShips();

protected:
    QSize getSizeObject(const QString input);
    ShipPosition getShipPosition(const QString input);
};

#endif // CONSOLEINTERFACE_H

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

    // Methods
    QString getPlayerName();
    QSize getBoardSize();
    QString getPositionForShip(const QString description);
    void drawGameBoard(Board &gameBoard);
    QHash<QString, int> getCustomShips();

protected:
    QSize getSizeObject(const QString input);
};

#endif // CONSOLEINTERFACE_H

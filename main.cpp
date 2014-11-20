#include "battleships.h"
#include "consoleinterface.h"
#include "board.h"


int main(int argc, char *argv[])
{
    Battleships battleships;
    ConsoleInterface interface;
    QString name = interface.getPlayerName();
    battleships.setPlayerName(name);
    QSize boardSize;
    do {
        boardSize = interface.getBoardSize();
    } while(! boardSize.isValid());
    Board gameBoard(boardSize.width(), boardSize.height());
    gameBoard.print();

    return 1;
}

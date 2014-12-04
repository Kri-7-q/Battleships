#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "battleships.h"
#include "consoleinterface.h"
#include "board.h"
#include "gameboardmodel.h"


int main(int argc, char *argv[])
{
    // If game was started with option -c it will launch in console.
    if (argc < 2 && QString(argv[1]) != "-c") {
        QApplication app(argc, argv);

        qmlRegisterType<GameBoardModel>("Models", 1, 0, "GameBoardModel");

        QQmlApplicationEngine engine;
        engine.load(QUrl(QStringLiteral("qrc:/GameGUI.qml")));

        return app.exec();

    } else {

        Battleships battleships;
        ConsoleInterface interface;
        // Player name
        QString name = interface.getPlayerName();
        battleships.setPlayerName(name);
        // Board size
        QSize boardSize;
        do {
            boardSize = interface.getBoardSize();
        } while(! boardSize.isValid());
        Board gameBoard(boardSize.width(), boardSize.height());
        // Want custom ships ?
        bool useCustomShips = interface.wantCustomShips();
        QHash<QString, int> shipSizeList;
        if (useCustomShips) {
            shipSizeList = interface.getCustomShips();
        } else {
            shipSizeList = battleships.getDefaultShips();
        }
        // Place ships
        QList<QString> shipNameList = shipSizeList.keys();
        for (QString description : shipNameList) {
            bool placed = false;
            while (! placed) {
                QString positionString = interface.getPositionForShip(description);
                ShipPosition position;
                if (positionString.isEmpty()) {
                    position = battleships.getRandomShipPosition(gameBoard.getGameBoardSize());
                } else {
                    position = battleships.getShipPosition(positionString);
                }
                int length = shipSizeList.value(description);
                placed = gameBoard.place(Ship(length), position.x, position.y, position.direction);
            }
        }
        // Game loop
        bool running = true;
        while (running) {
            interface.drawGameBoard(gameBoard);
            // Get shoot from player.
            QString input = interface.getShot();
            if (input == "quit") {
                interface.printText("Bye, Bye ...");
                break;
            }
            // Place shot on game board.
            QPoint shoot = battleships.getPointObject(input);
            if (! gameBoard.isWithinGameBoard(shoot)) {
                interface.printText("Shot was not within the game board.");
                continue;
            }
            bool isHit = gameBoard.shoot(shoot.x(), shoot.y());
            if (isHit) {
                interface.printText("A ship was hidden by this shot.");
            }
            battleships.addShoot();
            // Are there undestroyed ships left ?
            if (! gameBoard.hasUndestroyedShip()) {
                running = false;
                QString text = battleships.getPlayerName() + " you have destroyed all ships.";
                interface.printText(text);
                text = QString("You have taken %1 shots.").arg(battleships.getShotsFired());
                interface.printText(text);
            }
        }

        return 1;
    }
}

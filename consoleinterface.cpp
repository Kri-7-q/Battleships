#include "consoleinterface.h"

/**
 * Constructor
 * Constructs a user interface for console input
 * and output.
 */
ConsoleInterface::ConsoleInterface() :
    cin(stdin),
    cout(stdout)
{
}

/**
 * Ask the user for its name.
 * @return          The player name.
 */
QString ConsoleInterface::getPlayerName()
{
    cout << "\n\nEnter your name : " << endl;
    cout << "> ";

    return cin.readLine();
}

/**
 * Ask the user for the size of the game board.
 * @return          A string containing komma seperated number. The width and height.
 */
QSize ConsoleInterface::getBoardSize()
{
    cout << "How big do you wish the game board [width,height] ?" << endl;
    cout << "> ";
    QString input = cin.readLine();

    return getSizeObject(input);
}

/**
 * Get the position and direction for a specific battleship.
 * No input (empty string) if user wants the ship to be placed automatically.
 * Otherwise the returning string should contain komma seperated
 * coordinates and the direction.
 * @param description
 * @return
 */
QString ConsoleInterface::getPositionForShip(const QString description)
{
    cout << "Where would you like to place your " << description << " ?" << endl;
    cout << "[empty] place automaticaly. [x,y,d] position and direction (r)igth, (l)eft, (u)p, (d)own" << endl;
    cout << "> ";

    return cin.readLine();
}

/**
 * Takes a string with komma seperated integer values.
 * These values are put into a QSize object.
 * @param input     A string with to integer values komma seperated.
 * @return          A QSize object containing these values. Or (-1,-1) if string was invalid.
 */
QSize ConsoleInterface::getSizeObject(const QString input)
{
    QStringList value = input.split(',');
    if (value.size() < 2) {
        return QSize(-1, -1);
    }
    QSize objectSize;
    bool ok;
    int x = value[0].toInt(&ok);
    objectSize.setWidth( (ok) ? x : -1 );
    int y = value[1].toInt(&ok);
    objectSize.setHeight( (ok) ? y : -1 );

    return objectSize;
}

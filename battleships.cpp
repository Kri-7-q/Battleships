#include "battleships.h"

/**
 * Construtor
 * Constructs a Battleship object.
 */
Battleships::Battleships() :
    shotsFired(0)
{
    defaultShips.insert("Aircraft carrier", 5);
    defaultShips.insert("Battleship", 4);
    defaultShips.insert("Submarine", 3);
    defaultShips.insert("Cruiser", 3);
    defaultShips.insert("Destroyer", 2);
}

// Getter
QString Battleships::getPlayerName() const
{
    return playerName;
}

// Setter
void Battleships::setPlayerName(const QString name)
{
    playerName = name;
}


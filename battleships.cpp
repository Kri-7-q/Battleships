#include "battleships.h"

/**
 * Construtor
 * Constructs a Battleship object.
 */
Battleships::Battleships() :
    shotsFired(0)
{
}

// Getter
QString Battleships::getPlayerName() const
{
    return playerName;
}

// Setter
void Battleships::setPlayerName(const QString &value)
{
    playerName = value;
}


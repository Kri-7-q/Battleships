#include "battleships.h"

/**
 * Construtor
 * Constructs a Battleship object.
 */
Battleships::Battleships(QObject *parent) :
    QObject(parent),
    m_shotsFired(0),
    m_playerMode(SinglePlayer),
    m_playersGameBoard(0),
    m_foesGameBoard(0),
    m_isGameOver(false)
{
    m_defaultShips.insert("Aircraft carrier", 5);
    m_defaultShips.insert("Battleship", 4);
    m_defaultShips.insert("Submarine", 3);
    m_defaultShips.insert("Cruiser", 3);
    m_defaultShips.insert("Destroyer", 2);
}

// Getter
QString Battleships::playerName() const
{
    return m_playerName;
}
// Setter
void Battleships::setPlayerName(const QString name)
{
    if (m_playerName != name) {
        m_playerName = name;
        emit playerNameChanged();
    }
}

// Getter
bool Battleships::localePlayersTurn() const
{
    return m_localePlayersTurn;
}
// Setter
void Battleships::setLocalePlayersTurn(bool localePlayersTurn)
{
    if (m_localePlayersTurn != localePlayersTurn) {
        m_localePlayersTurn = localePlayersTurn;
        emit localePlayersTurnChanged();
    }
}


/**
 * Takes a string with komma seperated integr values for coordinates
 * and a letter to indicate ships direction.
 * These values are put into a ShipPosition object.
 * @param input                 A string with komma seperated values.
 * @return position             A ShipPosition object containing the values.
 */
ShipPosition Battleships::getShipPosition(const QString input)
{
    ShipPosition position = {-1, -1, Ship::Up};
    QStringList value = input.split(',');
    if (value.size() < 3) {
        return position;
    }
    bool ok;
    int x = value[0].toInt(&ok);
    position.x = (ok) ? x : -1 ;
    int y = value[1].toInt(&ok);
    position.y = (ok) ? y : -1 ;
    char *direction = value[2].toUtf8().data();
    switch (direction[0]) {
    case 'l':
        position.direction = Ship::Left;
        break;
    case 'r':
        position.direction = Ship::Right;
        break;
    case 'u':
        position.direction = Ship::Up;
        break;
    case 'd':
        position.direction = Ship::Down;
        break;
    default:
        position.direction = Ship::Down;
        break;
    }

    return position;
}

/**
 * Creates a random position and direction for a ship.
 * @param boardSize     The size of game board.
 * @return              A ShipPosition object with position and direction.
 */
ShipPosition Battleships::getRandomShipPosition(const QSize boardSize)
{
    qsrand(QTime::currentTime().msec());
    int x = qrand() % boardSize.width();
    int y = qrand() % boardSize.height();
    Ship::Direction dir = (Ship::Direction)(qrand() % 4);
    ShipPosition position = { x, y, dir };

    return position;
}

/**
 * Takes a string with komma seperated integer values.
 * These values are put into a QPoint object.
 * @param input     A string with to integer values komma seperated.
 * @return          A QPoint object containing these values. Or (-1,-1) if string was invalid.
 */
QPoint Battleships::getPointObject(const QString input)
{
    QStringList value = input.split(',');
    if (value.size() < 2) {
        return QPoint(-1, -1);
    }
    QPoint point;
    bool ok;
    int x = value[0].toInt(&ok);
    point.setX( (ok) ? x : -1 ) ;
    int y = value[1].toInt(&ok);
    point.setY( (ok) ? y : -1 );

    return point;
}

/**
 * SLOT
 * Set game board referenz.
 * @param board
 */
void Battleships::setPlayersGameBoard(Board *board)
{
    m_playersGameBoard = board;
}

/**
 * SLOT
 * Set game board referenz.
 * @param board
 */
void Battleships::setFoesGameBoard(Board *board)
{
    m_foesGameBoard = board;
}

/**
 * SLOT
 * Takes a shot from the local player.
 * @param index
 */
bool Battleships::playersShoot(const int index)
{
    setLocalePlayersTurn(false);
    addShoot();
    bool isHit = m_foesGameBoard->shootAt(index);
    if (isHit) {
        setInfoText("You did hit one of the ships.");
    } else {
        setInfoText("You shot into the water.");
    }
    if (! m_foesGameBoard->hasUndestroyedShip()) {
        setIsGameOver(true);
        setWinnerName(playerName());
    }
    if (m_playerMode == SinglePlayer) {
        emit botShoot();
    }

    return isHit;
}

/**
 * SLOT
 * Place ships for the oponent in sigle player mode.
 */
void Battleships::randomlyPlaceShips()
{
    QStringList shipNameList = m_defaultShips.keys();
    for (QString name : shipNameList) {
        bool isPlaced = false;
        do {
            ShipPosition position = getRandomShipPosition(m_foesGameBoard->getGameBoardSize());
            int shipLength = m_defaultShips.value(name);
            Ship ship(shipLength, name);
            isPlaced = m_foesGameBoard->place(ship, position.x, position.y, position.direction);
        } while(! isPlaced);
    }
}

// Q_PROPERTY - Getter
QString Battleships::winnerName() const
{
    return m_winnerName;
}
// Q_PROPERTY - Setter
void Battleships::setWinnerName(const QString &winnerName)
{
    if (m_winnerName != winnerName) {
        m_winnerName = winnerName;
        emit winnerNameChanged();
    }
}


// Q_PROPERTY - Getter
QString Battleships::infoText() const
{
    return m_infoText;
}
// Q_PROPERTY - Setter
void Battleships::setInfoText(const QString &infoText)
{
    if (m_infoText != infoText) {
        m_infoText = infoText;
        emit infoTextChanged();
    }
}


// Getter
Battleships::PlayerMode Battleships::playerMode() const
{
    return m_playerMode;
}
// Setter
void Battleships::setPlayerMode(const PlayerMode playerMode)
{
    if (m_playerMode != playerMode) {
        m_playerMode = playerMode;
        emit playerModeChanged();
    }
}



/**
 * Q_PROPERTY
 * Returns TRUE if game is over.
 * @return
 */
bool Battleships::isGameOver() const
{
    return m_isGameOver;
}

/**
 * Q_PROPERTY
 * Set the game over value.
 * @param isGameOver
 */
void Battleships::setIsGameOver(bool isGameOver)
{
    if (m_isGameOver != isGameOver) {
        m_isGameOver = isGameOver;
        emit isGameOverChanged();
    }
}

/**
 * Simulates a bot behaviour. Shoots randomly to the locale
 * players game board.
 * @return          True if bot hit a ship.
 */
bool Battleships::botShoot()
{
    ShipPosition position = getRandomShipPosition(m_playersGameBoard->getGameBoardSize());
    bool isHit = m_playersGameBoard->shoot(position.x, position.y);
    if (isHit) {
        setInfoText("One of your ships is hidden.");
    } else {
        setInfoText("Foe shot into the water.");
    }
    if (isHit && ! m_playersGameBoard->hasUndestroyedShip()) {
        setIsGameOver(true);
        setWinnerName("Foe");
    }
    setLocalePlayersTurn(true);

    return isHit;
}


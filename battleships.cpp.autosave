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
    m_isGameOver(false),
    m_interface(0),
    m_currentView("PlayerNameDialog")
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
 * Places the shot on the oponents board or send the
 * coordinates through the network.
 * @param index
 */
bool Battleships::playersShoot(const int index)
{
    setLocalePlayersTurn(false);
    addShoot();
    bool isHit = false;
    if (m_playerMode == SinglePlayer) {
        const Ship *hiddenShip = m_foesGameBoard->shootAt(index);
        if (hiddenShip) {
            setInfoText("You hit one of the ships.");
        } else {
            setInfoText("You shot into the water.");
        }
        if (! m_foesGameBoard->hasUndestroyedShip()) {
            setWinnerName(playerName());
            setCurrentView("GameOverDialog");
        }
        emit botShoot();
    } else {
        m_indexLastShot = index;
        QJsonObject object;
        object.insert("type", "SHOT");
        QJsonObject options;
        QPoint pt = m_foesGameBoard->getPointObject(index);
        options.insert("x", pt.x());
        options.insert("y", pt.y());
        object.insert("options", options);
        QJsonDocument *message = new QJsonDocument(object);
        emit sendMessage(message);
    }

    return isHit;
}

/**
 * SLOT
 * Place ships for the oponent in sigle player mode.
 */
void Battleships::randomlyPlaceShips(Board *gameBoard)
{
    gameBoard->removeAll();
    QStringList shipNameList = m_defaultShips.keys();
    for (QString name : shipNameList) {
        bool isPlaced = false;
        do {
            ShipPosition position = getRandomShipPosition(gameBoard->getGameBoardSize());
            int shipLength = m_defaultShips.value(name);
            Ship ship(shipLength, name);
            isPlaced = gameBoard->place(ship, position.x, position.y, position.direction);
        } while(! isPlaced);
    }
}

/**
 * SLOT
 * Is call if a message arrived from network.
 * @param message
 */
void Battleships::receiveMessage(QJsonDocument *message)
{
    if (message->isArray()) {
        QJsonArray array = message->array();
        for (int i=0; i<array.size(); ++i) {
            QJsonObject object = array.at(i).toObject();
            interpretJsonObject(object);
        }
    } else {
        QJsonObject object = message->object();
        interpretJsonObject(object);
    }
    delete message;
}

/**
 * SLOT
 * Send a replay message to a game offer.
 * @param name
 * @param accept
 */
void Battleships::sendGameOfferReplay(const QString name, const bool accept)
{
    QJsonObject object;
    object.insert("type", "GAME_OFFER_REPLAY");
    QJsonObject options;
    options.insert("player_name", name);
    options.insert("success", accept ? "true" : "false");
    object.insert("options", options);
    QJsonDocument *message = new QJsonDocument(object);
    emit sendMessage(message);
}

/**
 * Get the interfaces available from Networkinterface class.
 */
void Battleships::getNetworkInterfaceInfo()
{
    networkInterfcaeInfo = m_interface->getAdapterAndAddresses();
}

/**
 * SLOT
 * Get all available and connected network adapter.
 * Adapter names are the keys of info table.
 * @return      A list of network adapter.
 */
QStringList Battleships::getNetworkInterfaceList() const
{
    return networkInterfcaeInfo.keys();
}

/**
 * SLOT
 * Get IP addresses to a network adapter.
 * @param adapter
 * @return
 */
QStringList Battleships::getIpAddressList(const QString &adapter) const
{
    return networkInterfcaeInfo.value(adapter);
}

/**
 * SLOT
 * Start server.
 * @param address
 * @param port
 */
void Battleships::initializeServer(const QString address, const quint16 port)
{
    m_interface->initializeServer(address, port);
}

/**
 * SLOT
 * Connect to server.
 * @param address
 * @param port
 */
void Battleships::initializeClientConnection(const QString address, const quint16 port)
{
    m_interface->initializeClientConnection(address, port);
}

/**
 * SLOT
 * Is called if network connection is made.
 * In multi player mode it sends a game offer.
 */
void Battleships::hasConnection()
{
    if (m_playerMode == MultiPlayer) {
        QJsonObject object;
        object.insert("type", "GAME_OFFER");
        QJsonObject options;
        options.insert("player_name", m_playerName);
        options.insert("board_size_x", m_playersGameBoard->columns());
        options.insert("board_size_y", m_playersGameBoard->rows());
        options.insert("ships_present", "default");
        object.insert("options", options);
        QJsonDocument *message = new QJsonDocument(object);
        emit sendMessage(message);
    }
}

/**
 * SLOT
 * Is called when a network error occures.
 * @param error
 */
void Battleships::networkConnectionError(const QString &error)
{
    m_networkConnectionError = error;
    emit networkErrorChanged();
    setCurrentView("NetworkErrorDialog");
}

/**
 * Interpret incoming messages (QJsonObject).
 * @param object
 */
void Battleships::interpretJsonObject(const QJsonObject &object)
{
    if (object.value("type") == "SHOT") {
        takeShot(object);
    }
    if (object.value("type") == "SHOT_REPLAY") {
        shotReplay(object);
    }
    if (object.value("type") == "GAME_OFFER") {
        takeGameOffer(object);
    }
    if (object.value("type") == "GAME_OFFER_REPLAY") {
        gameOfferReplay(object);
    }
    if (object.value("type") == "FINISHED") {
        finishedMessage(object);
    }
}

/**
 * Take a shot from oponent.
 * Send replay message.
 * @param object
 */
void Battleships::takeShot(const QJsonObject &object)
{
    QJsonObject options = object.value("options").toObject();
    quint8 x = options.value("x").toInt();
    quint8 y = options.value("y").toInt();
    const Ship *hiddenShip = m_playersGameBoard->shoot(x, y);
    QJsonObject replayObject;
    replayObject.insert("type", "SHOT_REPLAY");
    QJsonObject replayOptions;
    replayObject.insert("options", replayOptions);
    if (hiddenShip != 0) {
        replayOptions.insert("result", "hit");
        if (hiddenShip->isDestroyed()) {
            replayOptions.insert("result", "sunk");
            replayOptions.insert("ship", hiddenShip->name());
            QList<QPoint> pointList = hiddenShip->getPointList();
            replayOptions.insert("fields", getJsonArrayOfPointList(pointList));
        }
        setInfoText("Incoming fire hit a ship.");
    } else {
        replayOptions.insert("result", "miss");
        setInfoText("Incoming fire goes into water.");
    }
    QJsonDocument *message = new QJsonDocument(replayObject);
    emit sendMessage(message);
    // Is game over ?
    if (hiddenShip->isDestroyed() && ! m_playersGameBoard->hasUndestroyedShip()) {
        QJsonObject finishedObject;
        finishedObject.insert("type", "FINISHED");
        QJsonObject finishedOptions;
        finishedOptions.insert("reason", "won");
        QJsonDocument *message = new QJsonDocument(finishedObject);
        emit sendMessage(message);
    }
    setLocalePlayersTurn(true);
}

/**
 * Interpret shot replay message.
 * @param object
 */
void Battleships::shotReplay(const QJsonObject &object)
{
    QModelIndex fieldIndex = m_foesGameBoard->index(m_indexLastShot);
    QJsonObject options = object.value("options").toObject();
    if (options.value("result") == "miss") {
        m_foesGameBoard->setData(fieldIndex, QVariant(Board::HiddenField), Board::ModifyFieldStateRole);
        setInfoText("Shot went into water.");
    }
    else if (options.value("result") == "hit") {
        m_foesGameBoard->setData(fieldIndex, QVariant(Board::HiddenShip), Board::ModifyFieldStateRole);
        setInfoText("You hit a ship.");
    }
    else if (options.value("result") == "sunk") {
        m_foesGameBoard->setData(fieldIndex, QVariant(Board::HiddenShip), Board::ModifyFieldStateRole);
        setInfoText(options.value("ship").toString() + " hit and sunk.");
    }
}

/**
 * Got a game offer.
 * Show terms of game offer on screen and ask the player
 * to accept it.
 * @param object
 */
void Battleships::takeGameOffer(const QJsonObject &object)
{
    QJsonObject options = object.value("options").toObject();
    QStringList list;
    list << options.value("player_name").toString();
    list << options.value("board_size_x").toString();
    list << options.value("board_size_y").toString();
    list << options.value("ships_present").toString();
    setGameOfferValueList(list);
    setCurrentView("GameOfferView");
}

/**
 * Got a game offer replay.
 * If game offer was accepted the game can start.
 * If not accepted ?
 * @param object
 */
void Battleships::gameOfferReplay(const QJsonObject &object)
{
    QJsonObject options = object.value("options").toObject();
    QString name = options.value("player_name").toString();
    bool accepted = options.value("success").toBool();
    if (accepted) {
        m_foesGameBoard->setPlayerName(name);
        setLocalePlayersTurn(true);
        setCurrentView("GamePlayDialog");
    }
}

/**
 * Got a finished message over network.
 * Interpret the reason.
 * @param object
 */
void Battleships::finishedMessage(const QJsonObject &object)
{
    QJsonObject options = object.value("options").toObject();
    if (options.value("reason") == "won") {
        setInfoText("You have won the game.");
        setWinnerName(m_playerName);
        setCurrentView("GameOverDialog");
    }
    else if (options.value("reason") == "quit") {
        setWinnerName("No one");
        setCurrentView("GameOverDialog");
    }
    else if (options.value("reason") == "error") {
        // Error ?
    }
    emit closeConnection();
}

/**
 * Takes a list of QPoint objects and creates a JSonArray
 * of it. The JsonArray contains a JsonObject for each point.
 * @param pointList
 * @return array
 */
QJsonArray Battleships::getJsonArrayOfPointList(const QList<QPoint> &pointList)
{
    QJsonArray array;
    for (QPoint point : pointList) {
        QJsonObject object;
        object.insert("x", point.x());
        object.insert("y", point.y());
        array.append(object);
    }

    return array;
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

// Getter
void Battleships::setNetworkInterface(NetworkInterface *interface)
{
    this->m_interface = interface;
}

// Q_PROPERTY - Getter
QStringList Battleships::gameOfferValueList()
{
    return m_gameOfferValueList;
}

//Q_PROPERTY - Setter
void Battleships::setGameOfferValueList(const QStringList &list)
{
    if (m_gameOfferValueList != list) {
        m_gameOfferValueList = list;
        emit gameOfferValueListChanged();
    }
}

// QPROPERTY - Setter
void Battleships::setCurrentView(const QString &view)
{
    if (m_currentView != view) {
        m_currentView = view;
        emit currentViewChanged();
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
 * Simulates a bot behaviour. Shoots randomly to the locale
 * players game board.
 * @return          True if bot hit a ship.
 */
bool Battleships::botShoot()
{
    ShipPosition position = getRandomShipPosition(m_playersGameBoard->getGameBoardSize());
    const Ship* hiddenShip = m_playersGameBoard->shoot(position.x, position.y);
    if (hiddenShip != 0) {
        setInfoText("One of your ships is hidden.");
    } else {
        setInfoText("Foe shot into the water.");
    }
    if (! m_playersGameBoard->hasUndestroyedShip()) {
        setWinnerName("Foe");
        setCurrentView("GameOverDialog");
    }
    setLocalePlayersTurn(true);

    return (hiddenShip != 0);
}


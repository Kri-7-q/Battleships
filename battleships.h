/**
  * Class Battleship
  * -------------------
  * Is the main class. It has the players name and
  * a shot counter of all shots taken.
  * It also keeps a default list of ships. Its a QHash table
  * with the ships name as key and the ships length as value.
  * The class can create a random position and direction for
  * a ship. And it converts input strings into usable values.
  */
#ifndef BATTLESHIPS_H
#define BATTLESHIPS_H
#include "Utilities.h"
#include "board.h"
#include <QStringList>
#include <QHash>
#include <QSize>
#include <QPoint>
#include <QObject>
#include <QTime>


class Battleships : public QObject
{
    Q_OBJECT
    Q_ENUMS(PlayerMode)
    Q_PROPERTY(QString playerName READ playerName WRITE setPlayerName NOTIFY playerNameChanged)
    Q_PROPERTY(Board* foesGameBoard WRITE setFoesGameBoard)
    Q_PROPERTY(Board* playersGameBoard WRITE setPlayersGameBoard)
    Q_PROPERTY(bool isGameOver READ isGameOver WRITE setIsGameOver NOTIFY isGameOverChanged)
    Q_PROPERTY(bool localePlayersTurn READ localePlayersTurn WRITE setLocalePlayersTurn NOTIFY localePlayersTurnChanged)
    Q_PROPERTY(PlayerMode playerMode READ playerMode WRITE setPlayerMode NOTIFY playerModeChanged)
    Q_PROPERTY(QString infoText READ infoText WRITE setInfoText NOTIFY infoTextChanged)
    Q_PROPERTY(QString winnerName READ winnerName WRITE setWinnerName NOTIFY winnerNameChanged)

public:
    explicit Battleships(QObject *parent = 0);

    enum PlayerMode { SinglePlayer, MultiPlayer };

    QString playerName() const;
    int shotsFired()                     { return m_shotsFired; }
    void setPlayerName(const QString name);
    QHash<QString,int> defaultShips()        { return m_defaultShips; }
    ShipPosition getShipPosition(const QString input);
    ShipPosition getRandomShipPosition(const QSize boardSize);
    void addShoot()                             { ++m_shotsFired; }
    QPoint getPointObject(const QString input);
    void setPlayersGameBoard(Board *board);
    void setFoesGameBoard(Board *board);
    bool isGameOver() const;
    void setIsGameOver(bool isGameOver);
    bool localePlayersTurn() const;
    void setLocalePlayersTurn(bool localePlayersTurn);
    PlayerMode playerMode() const;
    void setPlayerMode(const PlayerMode playerMode);
    QString infoText() const;
    void setInfoText(const QString &infoText);
    QString winnerName() const;
    void setWinnerName(const QString &winnerName);

signals:
    void playerNameChanged();
    void isGameOverChanged();
    void localePlayersTurnChanged();
    void playerModeChanged();
    void infoTextChanged();
    void winnerNameChanged();

public slots:
    bool botShoot();
    bool playersShoot(const int index);
    void randomlyPlaceShips();

private:
    QString m_playerName;
    int m_shotsFired;
    QHash<QString, int> m_defaultShips;
    PlayerMode m_playerMode;
    Board* m_playersGameBoard;
    Board* m_foesGameBoard;
    bool m_isGameOver;
    bool m_localePlayersTurn;
    QString m_infoText;
    QString m_winnerName;
};

#endif // BATTLESHIPS_H

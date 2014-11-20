#ifndef BATTLESHIPS_H
#define BATTLESHIPS_H
#include <QString>

class Battleships
{
public:
    Battleships();

    QString getPlayerName() const;
    void setPlayerName(const QString &value);

protected:
    QString playerName;
    quint16 shotsFired;
};

#endif // BATTLESHIPS_H

#ifndef BATTLESHIPS_H
#define BATTLESHIPS_H
#include <QString>
#include <QHash>


class Battleships
{
public:
    Battleships();

    QString getPlayerName() const;
    void setPlayerName(const QString name);
    QHash<QString,int> getDefaultShips()         { return defaultShips; }

protected:
    QString playerName;
    quint16 shotsFired;
    QHash<QString, int> defaultShips;
};

#endif // BATTLESHIPS_H

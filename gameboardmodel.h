#ifndef GAMEBOARDMODEL_H
#define GAMEBOARDMODEL_H

#include <QAbstractListModel>

class GameBoardModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit GameBoardModel(QObject *parent = 0);

signals:

public slots:


    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
};

#endif // GAMEBOARDMODEL_H

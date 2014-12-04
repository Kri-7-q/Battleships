#include "gameboardmodel.h"

GameBoardModel::GameBoardModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

int GameBoardModel::rowCount(const QModelIndex &parent) const
{
    return 5;
}

QVariant GameBoardModel::data(const QModelIndex &index, int role) const
{
    return QVariant();
}

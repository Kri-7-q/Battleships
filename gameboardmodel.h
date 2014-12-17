#ifndef GAMEBOARDMODEL_H
#define GAMEBOARDMODEL_H

#include <QAbstractListModel>
#include <QRect>
#include <QList>
#include "ship.h"


class GameBoardModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int columns READ columns WRITE setColumns NOTIFY columnsChanged)
    Q_PROPERTY(int rows READ rows WRITE setRows NOTIFY rowsChanged)
public:
    explicit GameBoardModel(QObject *parent = 0);

    enum UserRoles { ShipAtPositionRole = Qt::UserRole + 1,
                     HasUndestroiedShipRole,
                     ModifyFieldStateRole,
                     ModifyShipHealthRole,
                     PlaceShipsRole };
    enum FieldState { emptyField, hiddenField, hiddenShip, placedShip, tempShip };
    Q_ENUMS(FieldState)

private:
    QRect m_boardRect;
    QList<Ship> m_shipList;
    QHash<int, FieldState> m_fieldStateList;

signals:
    void columnsChanged();
    void rowsChanged();

public slots:

public:
    int columns() const             { return m_boardRect.width(); }
    int rows() const                { return m_boardRect.height(); }
    void setColumns(const int columns);
    void setRows(const int height);
    QRect gameBoardRect() const           { return m_boardRect; }

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QHash<int, QByteArray> roleNames() const;

protected:
    bool placeShipToGameBoard(const Ship &newShip, int topLeft, int bottomRight);
};

#endif // GAMEBOARDMODEL_H

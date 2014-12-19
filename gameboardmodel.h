#ifndef GAMEBOARDMODEL_H
#define GAMEBOARDMODEL_H

#include <QAbstractListModel>
#include <QRect>
#include <QList>
#include "ship.h"


class GameBoardModel : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(FieldState)
    Q_PROPERTY(int columns READ columns WRITE setColumns NOTIFY columnsChanged)
    Q_PROPERTY(int rows READ rows WRITE setRows NOTIFY rowsChanged)
    Q_PROPERTY(QString destroyedShipName READ destroyedShipName NOTIFY destroyedShipNameChanged)

public:
    explicit GameBoardModel(QObject *parent = 0);

    enum UserRoles { ShipAtPositionRole = Qt::UserRole + 1,
                     HasUndestroiedShipRole,
                     ModifyFieldStateRole,
                     ModifyShipHealthRole,
                     PlaceShipsRole,
                     DisplayAllRole };
    enum FieldState { EmptyField, HiddenField, HiddenShip, PlacedShip };

private:
    QRect m_boardRect;
    QList<Ship> m_shipList;
    QHash<int, FieldState> m_fieldStateList;
    QString m_destroyedShipName;

signals:
    void columnsChanged();
    void rowsChanged();
    void destroyedShipNameChanged();

public slots:
    void removeAll();

public:
    int columns() const             { return m_boardRect.width(); }
    int rows() const                { return m_boardRect.height(); }
    void setColumns(const int columns);
    void setRows(const int height);
    QRect gameBoardRect() const           { return m_boardRect; }
    FieldState fieldState() const;
    void setFieldState(const FieldState state);

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QHash<int, QByteArray> roleNames() const;
    QString destroyedShipName() const;
    void setDestroyedShipName(const QString &destroyedShipName);

protected:
    bool placeShipToGameBoard(const Ship &newShip, int topLeft, int bottomRight);
    QPoint getPointObject(const int fieldNumber) const;
};

#endif // GAMEBOARDMODEL_H

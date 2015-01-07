#ifndef NETWORKINTERFACE_H
#define NETWORKINTERFACE_H

/**
  * Class NetworkInterface
  * ------------------------
  * This class can start a server to receive a single connection
  * to a client. If the connected to a client the server is stopped.
  * A QTcpSocket object is instanziated in the heap.
  * If no server is needed because a connection to another server is
  * to be made a QTcpSocket will be instanziated in the heap. It tries
  * to achive a connection to a server.
  * With sendMessage() it can send Json objects through the network.
  * If a message arrives from remote it is read automatically and
  * the signal receivedMessage() is emitted.
  * (Both funktions add and remove an new line charackter to apply
  * to the protocol.)
  */

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QStringList>
#include <QHash>
#include <QNetworkInterface>

class NetworkInterface : public QObject
{
    Q_OBJECT
public:
    explicit NetworkInterface(QObject *parent = 0);

signals:
    void hasConnection();
    void receivedMessage(const QJsonDocument *messgae);

public slots:
    void initializeServer(const quint16 port);
    void initializeClientConnection(const QString serverAddress, const quint16 port);
    void sendMessage(const QJsonDocument *message);
    QJsonDocument* readMessage();
    void closeCennection();

private slots:
    void takeClientConnection();
    void clientConnected();
    QString socketError(QAbstractSocket::SocketError error);

public:
    QHash<QString, QStringList> getAdapterAndAddresses();

private:
    QTcpServer m_server;
    QTcpSocket *m_pSocket;

    QJsonDocument* getJsonDocument(const QList<QByteArray> messageList);
    QList<QNetworkInterface> getConnectedInterfaces();
};

#endif // NETWORKINTERFACE_H

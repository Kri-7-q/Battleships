#include "networkinterface.h"

/**
 * Constructor
 * @param parent
 */
NetworkInterface::NetworkInterface(QObject *parent) :
    QObject(parent),
    m_pSocket(0)
{
    m_server.setMaxPendingConnections(1);
    connect(&m_server, SIGNAL(newConnection()), this, SLOT(takeClientConnection()));
}

/**
 * SLOT
 * Initializes the QTcpServer to listen for incomming
 * connections.
 * @param port
 */
void NetworkInterface::initializeServer(const quint16 port)
{
    QHostAddress address("192.168.0.199");
    m_server.listen(address, port);
}

/**
 * SLOT
 * Client connected to the server. Take this connection.
 */
void NetworkInterface::takeClientConnection()
{
    m_pSocket = m_server.nextPendingConnection();
    m_server.close();
    connect(m_pSocket, SIGNAL(error()), this, SLOT(socketError()));
    connect(m_pSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    emit hasConnection();
}

/**
 * SLOT
 * Tries to connect to a server.
 * @param serverAddress
 * @param port
 */
void NetworkInterface::initializeClientConnection(const QString serverAddress, const quint16 port)
{
    m_pSocket = new QTcpSocket();
    connect(m_pSocket, SIGNAL(error()), this, SLOT(socketError()));
    connect(m_pSocket, SIGNAL(connected()), this, SLOT(clientConnected()));
    m_pSocket->connectToHost(serverAddress, port);
}

/**
 * SLOT
 * Is called when client has connection to the server.
 * Conects signal readyRead() of QAbstractSocket to slot readMessage().
 * Emits signal hasConnection().
 */
void NetworkInterface::clientConnected()
{
    connect(m_pSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    emit hasConnection();
}

/**
 * SLOT
 * Is called when QTcpSocket emits the signal error().
 */
QString NetworkInterface::socketError(QAbstractSocket::SocketError error)
{
    QString errorMessage;
    switch (error) {
    case QAbstractSocket::ConnectionRefusedError:
        errorMessage = "The connection was refused by the peer (or timed out).";
        break;
    case QAbstractSocket::RemoteHostClosedError:
        errorMessage = "The remote host closed the connection. Note that the client socket (i.e., this socket) will be closed after the remote close notification has been sent.";
        break;
    case QAbstractSocket::SocketAccessError:
        errorMessage = "The socket operation failed because the application lacked the required privileges.";
        break;
    case QAbstractSocket::SocketResourceError:
        errorMessage = "The local system ran out of resources (e.g., too many sockets).";
        break;
    case QAbstractSocket::SocketTimeoutError:
        errorMessage = "The socket operation timed out.";
        break;
    case QAbstractSocket::DatagramTooLargeError:
        errorMessage = "The datagram was larger than the operating system's limit (which can be as low as 8192 bytes).";
        break;
    case QAbstractSocket::NetworkError:
        errorMessage = "An error occurred with the network (e.g., the network cable was accidentally plugged out).";
        break;
    case QAbstractSocket::UnsupportedSocketOperationError:
        errorMessage = "The requested socket operation is not supported by the local operating system (e.g., lack of IPv6 support).";
        break;
    case QAbstractSocket::OperationError:
        errorMessage = "An operation was attempted while the socket was in a state that did not permit it.";
        break;
    default:
        errorMessage = "An unknown error occurred.";
        break;
    }

    return errorMessage;
}

/**
 * Creates a QHash with connected local network interfaces and ip addresses.
 * The interface name is the key of QHash. Whereas a list of ip addresses
 * is set as value.
 * @return              Interface name and ip list.
 */
QHash<QString, QStringList> NetworkInterface::getAdapterAndAddresses()
{
    QHash<QString, QStringList> connectionTable;
    QList<QNetworkInterface> interfaceList = getConnectedInterfaces();
    for (QNetworkInterface interface : interfaceList) {
        QStringList ipList;
        QList<QHostAddress> addressList = interface.allAddresses();
        for (QHostAddress address : addressList) {
            ipList << address.toString();
        }
        connectionTable.insert(interface.name(), ipList);
    }

    return connectionTable;
}

/**
 * Find local network interfaces which are connected to a network.
 * If a interface has a hardware address then it nust be a real
 * interface (not virtual). If these interfaces own one or a ip
 * address the it should be connected to any network.
 * @return      A list of connected network interfaces.
 */
QList<QNetworkInterface> NetworkInterface::getConnectedInterfaces()
{
    QList<QNetworkInterface> interfaceList = QNetworkInterface::allInterfaces();
    int i=0;
    while (i<=interfaceList.size()) {
        QNetworkInterface interface = interfaceList.at(i);
        if (interface.hardwareAddress().isEmpty() &&
            interface.allAddresses().isEmpty()) {
            interfaceList.removeFirst();
        } else {
            ++i;
        }
    }

    return interfaceList;
}

/**
 * Build a QJsonDocument from QByteArray's.
 * Returns a QJsonDocument containing a single object if
 * list has just one line. Other wise QJsonObject are returned
 * as a QJsonDocument containing a QJsonArray.
 * @param message
 * @return
 */
QJsonDocument *NetworkInterface::getJsonDocument(const QList<QByteArray> messageList)
{
    if (messageList.size() < 1) {
        return new QJsonDocument();
    }
    if (messageList.size() == 1) {
        return new QJsonDocument(QJsonDocument::fromJson(messageList.first()));
    }
    QJsonArray array;
    for (QByteArray byteArray : messageList) {
        QJsonObject object = QJsonDocument::fromJson(byteArray).object();
        array.append(object);
    }

    return new QJsonDocument(array);
}

/**
 * SLOT
 * Send a message. Takes a QJsonDocument pointer. This document
 * can consist of a single QJsonObject or an QJsonArray.
 * @param message       The message as a Json object.
 */
void NetworkInterface::sendMessage(const QJsonDocument *message)
{
    QByteArray data;
    if (message->isObject()) {
        data = message->toJson(QJsonDocument::Compact) + '\n';
    } else {
        QJsonArray array = message->array();
        for (int i=0; i<array.size(); ++i) {
            QJsonDocument document = QJsonDocument(array.at(i).toObject());
            data.append(document.toJson(QJsonDocument::Compact) + '\n');
        }
    }
    m_pSocket << data;
    m_pSocket->flush();
}

/**
 * SLOT
 * Read an incomming message from the socket.
 * Message can contain one or more lines. A single line message will
 * be returned as a QJsonDocument containing a QJsonObject. If more lines
 * are send a QJsonArray is returned in a QJsonDocument.
 * Emits the signal receivedMessage() when message is read.
 * @return message      The received message as a Json object (QJsonDocument).
 */
QJsonDocument* NetworkInterface::readMessage()
{
    QList<QByteArray> messageList;
    while (m_pSocket->bytesAvailable()) {
        QByteArray data = m_pSocket->readLine();
        if (data.endsWith('\n')) {
            data.truncate(data.length()-1);
        }
        messageList.append(data);
    }
    QJsonDocument *pJsonDocument = getJsonDocument(messageList);
    emit receivedMessage(pJsonDocument);

    return pJsonDocument;
}

/**
 * SLOT
 * Closes the network connection and delete the QTcpSocket object.
 */
void NetworkInterface::closeCennection()
{
    if (m_pSocket == 0) {
        return;
    }
    m_pSocket->close();
    m_pSocket->disconnect();
    delete m_pSocket;
    m_pSocket = 0;
}

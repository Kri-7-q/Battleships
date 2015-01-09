#include "battleships.h"
#include "consoleinterface.h"
#include "networkinterface.h"
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Battleships controler;
    NetworkInterface interface;
    controler.setNetworkInterface(&interface);
    QObject::connect(&interface, SIGNAL(receivedMessage(QJsonDocument*)), &controler, SLOT(receiveMessage(QJsonDocument*)));
    QObject::connect(&controler, SIGNAL(sendMessage(QJsonDocument*)), &interface, SLOT(sendMessage(QJsonDocument*)));
    QObject::connect(&interface, SIGNAL(hasConnection()), &controler, SLOT(hasConnection()));
    QObject::connect(&interface, SIGNAL(networkError(QString)), &controler, SLOT(networkConnectionError(QString)));

    qmlRegisterType<Board>("Models", 1, 0, "GameBoardModel");
    qmlRegisterType<Battleships>("Controler", 1, 0, "Controler");
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("controler", &controler);
    engine.load(QUrl(QStringLiteral("qrc:/GameGUI.qml")));

    return app.exec();

}

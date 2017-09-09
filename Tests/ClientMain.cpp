//
// Created on 2017/09/08 at 10:12.
//

#include <QApplication>
#include <QtCore/QTimer>
#include "../Controllers/Network/Client.hpp"


int main(int argc, char **argv)
{
    QApplication application(argc, argv);

    Client client;
    client.SetRemoteServerAddress("localhost");
    client.SetRemoteServerPort(6666);
    client.RegisterToHost();
    client.SendMessage("Hello server");

    //    QEventLoop eventLoop;
    //    QTimer::singleShot(1000, &eventLoop, &QEventLoop::quit);
    //    eventLoop.exec();

    return application.exec();
}
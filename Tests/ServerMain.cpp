//
// Created on 2017/09/08 at 10:12.
//

#include <QCoreApplication>
#include "../Controllers/Network/Server.hpp"


int main(int argc, char **argv)
{
    QCoreApplication application(argc, argv);

    Server server;
    server.SetServerPort(6666);
    server.StartServing();

    return application.exec();
}
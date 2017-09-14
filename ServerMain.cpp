//
// Created on 2017/09/09 at 22:54.
//

#include <QtCore/QCoreApplication>
#include "Controllers/RemoteController.hpp"
#include <iostream>


int main(int argc, char **argv)
{
    std::cout << "input port: ";
    int port;
    std::cin >> port;

    QCoreApplication application(argc, argv);

    RemoteController remoteController;
    remoteController.SetServerPort(port);
    remoteController.StartServing();

    return application.exec();
}

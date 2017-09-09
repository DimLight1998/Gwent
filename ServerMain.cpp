//
// Created on 2017/09/09 at 22:54.
//

#include <QtCore/QCoreApplication>
#include "Controllers/RemoteController.hpp"


int main(int argc, char **argv)
{
    QCoreApplication application(argc, argv);

    RemoteController remoteController;
    remoteController.SetServerPort(6666);
    remoteController.StartServing();

    return application.exec();
}

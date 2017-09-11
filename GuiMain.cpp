//
// Created on 2017/09/11 at 15:44.
//

#include <QApplication>
#include "Views/BaseWindow.hpp"


int main(int argc, char **argv)
{
    QApplication application(argc, argv);

    BaseWindow baseWindow;
    baseWindow.show();

    return application.exec();
}

//
// Created on 2017/09/11 at 15:44.
//

#include <QApplication>
#include "Views/BaseWindow.hpp"
#include <QTranslator>


int main(int argc, char **argv)
{
    QApplication application(argc, argv);

    QTranslator translator;
    translator.load("Chinese.qm");
    application.installTranslator(&translator);

    BaseWindow baseWindow;
    baseWindow.show();

    return application.exec();
}

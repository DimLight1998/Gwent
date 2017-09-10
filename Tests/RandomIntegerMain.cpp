//
// Created on 2017/09/10 at 14:36.
//

#include <QtCore/QCoreApplication>
#include "../Utilities/RandomInteger.hpp"
#include <QDebug>


int main(int argc, char **argv)
{
    QCoreApplication application(argc, argv);

    int al = RandomInteger::GetRandomInteger();
    qDebug() << al;

    return application.exec();
}
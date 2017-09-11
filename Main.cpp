//
// Created on 2017/09/03 at 14:01.
//
#include <QApplication>
#include <iostream>
#include "Controllers/GameController.hpp"


int main(int argc, char **argv)
{
    std::cout << "Welcome to Gwent in command line!\n";
    QApplication application(argc, argv);

    GameController gameController;
    gameController.StartGameEntry();

    return application.exec();
}

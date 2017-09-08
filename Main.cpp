//
// Created on 2017/09/03 at 14:01.
//
#include <QApplication>
#include <iostream>
#include "Controllers/GameController.hpp"


int main(int argc, char **argv)
{
    std::cout << "Welcome to Gwent in command line!\n";

    GameController gameController;
    gameController.StartGame();

    //    QApplication application(argc, argv);
    //    return application.exec();
}

//
// Created on 2017/09/09 at 22:39.
//

#include "RemoteController.hpp"


void RemoteController::HandleMessage(const QString& message)
{
    if (message.startsWith("PLAYER"))
    {
        auto ip   = message.split('|')[1];
        auto port = message.split('|')[2];

        auto response = QString();
        response = QString("ALLOCATE|%1|%2|%3").arg(ip).arg(port).arg(PlayerCounter);

        Broadcast(response);

        PlayerCounter++;

        // in case you forget to call ResetServerData
        if (PlayerCounter == 2)
        {
            PlayerCounter = 0;
        }
    }
}


void RemoteController::ResetServerData()
{
    PlayerCounter = 0;
}

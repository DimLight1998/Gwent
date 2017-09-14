//
// Created on 2017/09/09 at 22:39.
//

#include <QtCore/QDateTime>
#include "RemoteController.hpp"


void RemoteController::HandleMessage(const QString& message)
{
    if (message.startsWith("PLAYER"))
    {
        auto ip   = message.split('|', QString::SkipEmptyParts)[1];
        auto port = message.split('|', QString::SkipEmptyParts)[2];

        auto response = QString();
        response = QString("ALLOCATE|%1|%2|%3").arg(ip).arg(port).arg(PlayerCounter);

        Broadcast(response);

        PlayerCounter++;

        // in case you forget to call ResetServerData and decide who starts first
        if (PlayerCounter == 2)
        {
            QStringList first;
            qsrand(static_cast<uint>(QDateTime::currentMSecsSinceEpoch()));

            for (int i = 0; i < 3; i++)
            {
                int isFirst = qrand() % 2;
                first.append(QString::number(isFirst));
            }

            auto broadcastInfo = "FIRST|" + first.join('|');
            Broadcast(broadcastInfo);

            qDebug() << "Broadcasted" << broadcastInfo;

            PlayerCounter = 0;
        }
    }

    if (message.startsWith("READYUNLOCK"))
    {
        NumPlayerReadyUnlock++;
        if (NumPlayerReadyUnlock == 2)
        {
            NumPlayerReadyUnlock = 0;
            Broadcast("UNLOCK");
        }
    }
}


void RemoteController::ResetServerData()
{
    PlayerCounter = 0;
}

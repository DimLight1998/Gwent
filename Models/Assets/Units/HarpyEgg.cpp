//
// Created on 2017/09/04 at 15:08.
//

#include <QtCore/QDateTime>
#include "HarpyEgg.hpp"


HarpyEgg::HarpyEgg()
{
    CardMetaInfo = CardMeta::GetMetaByCardName("HarpyEgg");
}


void HarpyEgg::OnDeathWish()
{
    qsrand(static_cast<uint>(QDateTime::currentMSecsSinceEpoch()));
    auto    randomNumber = qrand() % 3;
    QString deployLine;

    if (randomNumber == 0)
    {
        deployLine = "AlliedSiege";
    }
    if (randomNumber == 1)
    {
        deployLine = "AlliedRanged";
    }
    if (randomNumber == 2)
    {
        deployLine = "AlliedMelee";
    }

    GlobalGameController->SpanCard("HarpyHatchling", deployLine, -1);
}

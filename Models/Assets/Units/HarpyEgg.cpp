//
// Created on 2017/09/04 at 15:08.
//

#include <QtCore/QDateTime>
#include "HarpyEgg.hpp"
#include "../../Meta/UnitMeta.hpp"


HarpyEgg::HarpyEgg(GameController *gameController)
    : Unit(gameController)
{
    CardMetaInfo = CardMeta::GetMetaByCardName("HarpyEgg");
    Power        = dynamic_cast<UnitMeta *>(CardMetaInfo)->GetInitialPower();
}


void HarpyEgg::OnDeathWish()
{
    Card::OnDeploy();

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

    GlobalGameController->SpawnCard("HarpyHatchling", deployLine, -1);
}


void HarpyEgg::OnDestroy()
{
    OnDeathWish();
    GlobalGameController->MoveCardFromCardsSetToCardsSet(CardId, GetFactionString() + "Discard", 0);
}


int HarpyEgg::GetPowerUpWhenSwallowed()
{
    return Power + 5;
}

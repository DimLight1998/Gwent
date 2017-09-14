//
// Created on 2017/09/04 at 16:23.
//

#include "RabidWolf.hpp"
#include "../../Meta/UnitMeta.hpp"


RabidWolf::RabidWolf(GameController *gameController)
    : Unit(gameController)
{
    CardMetaInfo = CardMeta::GetMetaByCardName("RabidWolf");
    Power        = dynamic_cast<UnitMeta *>(CardMetaInfo)->GetInitialPower();
}


void RabidWolf::OnDestroy()
{
    Card::OnDeploy();

    GlobalGameController->MoveCardFromCardsSetToCardsSet(CardId, GetFactionString() + "Discard", 0);
}

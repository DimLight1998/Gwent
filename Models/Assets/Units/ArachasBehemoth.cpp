//
// Created on 2017/09/06 at 01:01.
//

#include "ArachasBehemoth.hpp"
#include "../../Meta/UnitMeta.hpp"


ArachasBehemoth::ArachasBehemoth(GameController *gameController)
    : Unit(gameController)
{
    CardMetaInfo = CardMeta::GetMetaByCardName("ArachasBehemoth");
    Power        = dynamic_cast<UnitMeta *>(CardMetaInfo)->GetInitialPower();
}


void ArachasBehemoth::OnDeploy()
{
    GainArmor(2);
}


void ArachasBehemoth::OnDestroy()
{
    GlobalGameController->MoveCardFromCardsSetToCardsSet(CardId, GetFactionString() + "Grave", 0);
}

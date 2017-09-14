//
// Created on 2017/09/04 at 11:01.
//

#include "Arachas.hpp"
#include "../../Meta/UnitMeta.hpp"


Arachas::Arachas(GameController *gameController)
    : Unit(gameController)
{
    CardMetaInfo = CardMeta::GetMetaByCardName("Arachas");
    Power        = dynamic_cast<UnitMeta *>(CardMetaInfo)->GetInitialPower();
}


void Arachas::OnDeploy()
{
    Card::OnDeploy();

    // todo maybe incorrect
    bool success = true;

    while (success)
    {
        success = GlobalGameController->DeployUnitFromContainerToBattleLine(
            "Arachas", "AlliedDeck", SelectedLine, SelectedIndex + 1
        );
    }
}


void Arachas::OnDestroy()
{
    GlobalGameController->MoveCardFromCardsSetToCardsSet(CardId, GetFactionString() + "Grave", 0);
}

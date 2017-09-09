//
// Created on 2017/09/05 at 19:42.
//

#include "GeEls.hpp"
#include "../../Containers/CardContainer.hpp"
#include "../../Meta/UnitMeta.hpp"


GeEls::GeEls(GameController *gameController)
    : Unit(gameController)
{
    CardMetaInfo = CardMeta::GetMetaByCardName("GeEls");
    Power        = dynamic_cast<UnitMeta *>(CardMetaInfo)->GetInitialPower();
}


void GeEls::OnDeploy()
{
    GlobalGameController->HandleGoldCardDeploying();

    auto hasSilver = false;
    auto hasGold   = false;
    int  silverId  = 0;
    int  goldId    = 0;

    for (const auto i:GlobalGameController->GetBattleField()->GetCardContainerByName("AlliedDeck")->GetCards())
    {
        auto cardType = GlobalGameController->GetCardManager()->GetCardById(i)->GetCardMetaInfo()->GetCardType();
        if (cardType == CardMeta::CardTypeEnum::Silver && !hasSilver)
        {
            hasSilver = true;
            silverId  = i;
        }
        else if (cardType == CardMeta::CardTypeEnum::Gold && !hasGold)
        {
            hasGold = true;
            goldId  = i;
        }
    }

    if (!hasGold && !hasSilver)
    {
        return;
    }

    if (!hasGold && hasSilver)
    {
        // DeployTheCardOfId has handle the removing, don't need to care about this
        // GlobalGameController->GetBattleField()->GetCardContainerByName("AlliedDeck")->RemoveCardOfId(silverId);
        GlobalGameController->DeployTheCardOfId(silverId);
    }

    if (hasGold && !hasSilver)
    {
        // DeployTheCardOfId has handle the removing, don't need to care about this
        // GlobalGameController->GetBattleField()->GetCardContainerByName("AlliedDeck")->RemoveCardOfId(goldId);
        GlobalGameController->DeployTheCardOfId(goldId);
    }

    if (hasGold && hasSilver)
    {
        auto choose = GlobalGameController->GetInteracting()
            ->GetSelectedCardFromExistingCards(QVector<int>({goldId, silverId}));

        // DeployTheCardOfId has handle the removing, don't need to care about this
        // GlobalGameController->GetBattleField()->GetCardContainerByName("AlliedDeck")->RemoveCardOfId(silverId);
        // GlobalGameController->GetBattleField()->GetCardContainerByName("AlliedDeck")->RemoveCardOfId(goldId);

        if (choose == goldId)
        {
            GlobalGameController->MoveCardFromCardsSetToCardsSet(silverId, "AlliedDeck", "AlliedDeck", 0);
            // GlobalGameController->GetBattleField()->GetCardContainerByName("AlliedDeck")->InsertCard(silverId, 0);
        }
        else if (choose == silverId)
        {
            GlobalGameController->MoveCardFromCardsSetToCardsSet(goldId, "AlliedDeck", "AlliedDeck", 0);
            // GlobalGameController->GetBattleField()->GetCardContainerByName("AlliedDeck")->InsertCard(goldId, 0);
        }

        GlobalGameController->DeployTheCardOfId(choose);
    }
}

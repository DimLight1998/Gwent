//
// Created on 2017/09/05 at 19:42.
//

#include "GeEls.hpp"
#include "../../Containers/CardContainer.hpp"


GeEls::GeEls()
{
    CardMetaInfo = CardMeta::GetMetaByCardName("GeEls");
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
        GlobalGameController->GetBattleField()->GetCardContainerByName("AlliedDeck")->RemoveCardOfId(silverId);
        GlobalGameController->DeployTheCardOfId(silverId);
    }

    if (hasGold && !hasSilver)
    {
        GlobalGameController->GetBattleField()->GetCardContainerByName("AlliedDeck")->RemoveCardOfId(goldId);
        GlobalGameController->DeployTheCardOfId(goldId);
    }

    if (hasGold && hasSilver)
    {
        auto choose = GlobalGameController->GetInteracting()
            ->GetSelectedCardFromExistingCards(QVector<int>({goldId, silverId}));

        GlobalGameController->GetBattleField()->GetCardContainerByName("AlliedDeck")->RemoveCardOfId(silverId);
        GlobalGameController->GetBattleField()->GetCardContainerByName("AlliedDeck")->RemoveCardOfId(goldId);

        if (choose == goldId)
        {
            GlobalGameController->GetBattleField()->GetCardContainerByName("AlliedDeck")->InsertCard(silverId, 0);
        }
        else if (choose == silverId)
        {
            GlobalGameController->GetBattleField()->GetCardContainerByName("AlliedDeck")->InsertCard(goldId, 0);
        }

        GlobalGameController->DeployTheCardOfId(choose);
    }
}

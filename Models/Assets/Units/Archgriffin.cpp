//
// Created on 2017/09/05 at 16:48.
//

#include "Archgriffin.hpp"
#include "../../Containers/CardContainer.hpp"


Archgriffin::Archgriffin()
{
    CardMetaInfo = CardMeta::GetMetaByCardName("Archgriffin");
}


void Archgriffin::OnDeploy()
{
    GlobalGameController->SetWeatherToBattleLine(SelectedLine, BattleLine::WeatherEnum::None);

    auto enemyGrave  = GlobalGameController->GetBattleField()->GetCardContainerByName("EnemyGrave")->GetCards();
    auto alliedGrave = GlobalGameController->GetBattleField()->GetCardContainerByName("AlliedGrave")->GetCards();

    auto grave = enemyGrave;

    grave.append(alliedGrave);

    for (int i = grave.size() - 1; i >= 0; i--)
    {
        auto isValid = false;

        if (GlobalGameController->GetCardManager()->GetCardById(grave[i])->GetCardMetaInfo()->GetCardType()
            == CardMeta::CardTypeEnum::Bronze)
        {
            if (Unit::IsCardUnit(GlobalGameController->GetCardManager()->GetCardById(grave[i])))
            {
                isValid = true;
            }
        }

        if (!isValid)
        {
            grave.remove(i);
        }
    }

    int id = GlobalGameController->GetInteracting()->GetSelectedCardFromExistingCards(grave);

    if (GlobalGameController->GetBattleField()->GetCardContainerByName("EnemyGrave")->IsCardContainerContainingCard(id))
    {
        GlobalGameController->MoveCardFromCardsSetToCardsSet(id, "EnemyGrave", "AlliedGrave", 0);
    }
    else if (GlobalGameController->GetBattleField()->GetCardContainerByName("AlliedGrave")
        ->IsCardContainerContainingCard(id))
    {
        GlobalGameController->MoveCardFromCardsSetToCardsSet(id, "AlliedGrave", "EnemyGrave", 0);
    }
}

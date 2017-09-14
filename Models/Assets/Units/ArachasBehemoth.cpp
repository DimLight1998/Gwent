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
    Card::OnDeploy();

    GainArmor(2);
}


void ArachasBehemoth::OnDestroy()
{
    GlobalGameController->MoveCardFromCardsSetToCardsSet(CardId, GetFactionString() + "Grave", 0);
}


void ArachasBehemoth::OnOtherUnitSwallowedHandler(int unitId)
{
    Card::OnOtherUnitSwallowedHandler(0);
    for (const auto& lineName:QVector<QString>({QString("Melee"), QString("Ranged"), QString("Siege")}))
    {
        auto battleLineName = "Allied" + lineName;

        for (const auto item:GlobalGameController->GetBattleField()->GetBattleLineByName(battleLineName)->GetUnits())
        {
            if (GlobalGameController->GetCardManager()->GetCardById(item)->GetCardMetaInfo()->GetName()
                == "ArachasBehemoth")
            {
                dynamic_cast<Unit *>(GlobalGameController->GetCardManager()->GetCardById(item))
                    ->DamageIgnoringArmorAndShield(1);

                // deploy arachas hatchling
                auto arachasHatchling = CardMeta::GetMetaByCardName("ArachasHatchling");
                GlobalGameController->GetInteracting()
                    ->GetSelectedCardFromSpanningCards(QVector<CardMeta *>({arachasHatchling}));
                delete arachasHatchling;

                auto id = GlobalGameController->SpawnCard("ArachasHatchling", "AlliedHand", 0);
                GlobalGameController->DeployTheCardOfId(id);
                GlobalGameController->GetInteracting()->SetCheckPoint();
            }
        }
    }
}

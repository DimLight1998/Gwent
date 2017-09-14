//
// Created on 2017/09/04 at 10:44.
//

#include <QtCore/QDateTime>
#include "Roach.hpp"
#include "../../Meta/UnitMeta.hpp"


Roach::Roach(GameController *gameController)
    : Unit(gameController)
{
    CardMetaInfo = CardMeta::GetMetaByCardName("Roach");
    Power        = dynamic_cast<UnitMeta *>(CardMetaInfo)->GetInitialPower();
}


void Roach::OnDestroy()
{
    GlobalGameController->MoveCardFromCardsSetToCardsSet(CardId, GetFactionString() + "Grave", 0);
}


void Roach::OnDeploy()
{
    Card::OnDeploy();
}


void Roach::OnOtherCardDeployHandler(int cardId)
{
    if (GlobalGameController->GetCardManager()->GetCardById(cardId)->GetCardMetaInfo()->GetCardType()
        == CardMeta::CardTypeEnum::Gold)
    {
        qsrand(static_cast<uint>(QDateTime::currentMSecsSinceEpoch()));
        auto lineNumber = qrand() % 3;
        auto lineName   = QVector<QString>({QString("AlliedSiege"),
                                            QString("AlliedRanged"),
                                            QString("AlliedMelee")})[lineNumber];

        auto size  = GlobalGameController->GetBattleField()->GetBattleLineByName(lineName)->GetUnits().size();
        auto index = qrand() % (size + 1);

        GlobalGameController->DeployUnitFromContainerToBattleLine("Roach", "AlliedDeck", lineName, index);
        GlobalGameController->GetInteracting()->SetCheckPoint();
    }
}

//
// Created on 2017/09/05 at 11:04.
//

#include <QtCore/QDateTime>
#include "Rally.hpp"
#include "../../Containers/CardContainer.hpp"
#include "../../Meta/UnitMeta.hpp"


Rally::Rally()
{
    CardMetaInfo = CardMeta::GetMetaByCardName("Rally");
}


void Rally::OnDeploy()
{
    QVector<int> bronzeUnits;

    for (auto id:GlobalGameController->GetBattleField()->GetCardContainerByName("AlliedDeck")->GetCards())
    {
        auto cardType   = GlobalGameController->GetCardManager()->GetCardById(id)->GetCardMetaInfo()->GetCardType();
        auto isUnitCard = Unit::IsCardUnit(GlobalGameController->GetCardManager()->GetCardById(id));

        if (cardType == CardMeta::CardTypeEnum::Bronze && isUnitCard)
        {
            bronzeUnits.append(id);
        }
    }

    if (bronzeUnits.empty())
    {
        return;
    }

    qsrand(static_cast<uint>(QDateTime::currentMSecsSinceEpoch()));
    auto index = qrand() % bronzeUnits.size();

    auto deployingCardId = bronzeUnits[index];

    QString deployLine;
    int     deployIndex;

    bool isLoyal = dynamic_cast<UnitMeta *>(GlobalGameController->GetCardManager()->GetCardById(deployingCardId)
        ->GetCardMetaInfo())->IsLoyal();

    bool isValid = false;

    do
    {
        GlobalGameController->GetInteracting()->GetSelectedUnitDeployLocation(deployLine, deployIndex);

        if (isLoyal)
        {
            isValid = deployLine.startsWith("Allied");
        }
        else
        {
            isValid = deployLine.startsWith("Enemy");
        }

        if (isValid)
        {
            GlobalGameController->DeployUnitToBattleLine(deployingCardId, deployLine, deployIndex);
        }
    }
    while (!isValid);
}

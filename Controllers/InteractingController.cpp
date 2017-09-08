//
// Created on 2017/09/05 at 09:58.
//

#include "InteractingController.hpp"
#include "GameController.hpp"
#include <QDebug>
#include <iostream>


GameController *InteractingController::GetController() const
{
    return Controller;
}


void InteractingController::SetController(GameController *Controller)
{
    InteractingController::Controller = Controller;
}


int InteractingController::GetSelectedCardFromExistingCards(const QVector<int>& existingCardsId)
{
    // todo switch to GUI
    std::cout << "You need to choose one card from the follow cards:\n";
    for (const auto i:existingCardsId)
    {
        auto card = Controller->GetCardManager()->GetCardById(i);
        std::cout << "Card Name: " << card->GetCardMetaInfo()->GetName().toStdString() << " Card Id: "
                  << card->GetCardId() << std::endl;
    }
    std::cout << "Choose one from the cards above, enter id" << std::endl;
    int input;
    std::cin >> input;
    return input;
}
// todo functions bellow

int InteractingController::GetSelectedCardFromExistingCardsAbdicable(const QVector<int>& existingCardsId)
{
    return 0;
}


void InteractingController::GetRoundInput(bool& abdicate, int& selectedCardId)
{
    std::cout
        << "[ Intercating ] Input a integer,"
            " -1 represents abdicate the round, others represent the card id you want to deploy";

    int input;
    std::cin >> input;

    if (input == -1)
    {
        abdicate       = true;
        selectedCardId = -1;
    }
    else
    {
        abdicate       = false;
        selectedCardId = input;
    }
}


CardMeta InteractingController::GetSelectedCardFromSpanningCards(const QVector<CardMeta *>& spawningCardsMeta)
{
    return CardMeta();
}


int InteractingController::GetSelectedCardFromBattleField()
{
    return 0;
}


int InteractingController::GetSelectedCardFromBattleField(const QVector<int>& filter)
{
    return 0;
}


void InteractingController::GetSelectedUnitDeployLocation(QString& deployBattleLine, int& deployIndex)
{
}


QString InteractingController::GetSelectedEffectDeployBattleLine()
{
    return QString();
}


void InteractingController::GetGlobalSelection()
{
}


InteractingController::InteractingController(GameController *Controller)
    : Controller(Controller)
{ }

//
// Created on 2017/09/05 at 09:58.
//

#include "InteractingController.hpp"
#include "GameController.hpp"
#include <iostream>
#include <QtWidgets/QInputDialog>
#include "../Models/Containers/CardContainer.hpp"


GameController *InteractingController::GetController() const
{
    return Controller;
}


InteractingController::InteractingController(GameController *Controller)
    : Controller(Controller)
{ }


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
    //    int input = QInputDialog::getInt(nullptr, "", "");
    int input;
    std::cin >> input;
    return input;
}
// todo functions bellow

int InteractingController::GetSelectedCardFromExistingCardsAbdicable(const QVector<int>& existingCardsId)
{
    std::cout << "Choose a card from the following cards\nYou can input -1 to abdicate\n";
    for (const auto item:existingCardsId)
    {
        std::cout << Controller->GetCardManager()->GetCardById(item)->ToDisplayableString().toStdString() << std::endl;
    }

    //    int index = QInputDialog::getInt(nullptr, "", "");
    int index;
    std::cin >> index;
    if (index == -1)
    {
        return -1;
    }
    else
    {
        return index;
    }
}


void InteractingController::GetRoundInput(bool& abdicate, int& selectedCardId)
{
    std::cout
        << "[ Intercating ] Input a integer,"
            " -1 represents abdicate the round, others represent the card id you want to deploy";

    //    int input = QInputDialog::getInt(nullptr, "", "");
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
    std::cout << "Choose a card from the following cards\n";
    for (int i = 0; i < spawningCardsMeta.size(); i++)
    {
        std::cout << i << " " << spawningCardsMeta[i]->GetName().toStdString() << std::endl;
    }

    //    int index = QInputDialog::getInt(nullptr, "", "");
    int index;
    std::cin >> index;

    return *(spawningCardsMeta[index]);
}


int InteractingController::GetSelectedCardFromBattleField()
{
    std::cout << "Select a card from the battle field\n";

    auto displayBattleLine = [this](QString name)
    {
      auto units = Controller->GetBattleField()->GetBattleLineByName(name)->GetUnits();
      std::cout << "Line " << name.toStdString() << std::endl;
      for (const auto item:units)
      {
          std::cout << Controller->GetCardManager()->GetCardById(item)->ToDisplayableString().toStdString()
                    << std::endl;
      }
    };

    for (const auto& prefix:QVector<QString>({"Enemy", "Allied"}))
        for (const auto& postfix:QVector<QString>({"Siege", "Ranged", "Melee"}))
        {
            displayBattleLine(prefix + postfix);
        }

    std::cout << "Input the id of the card";
    //    int input = QInputDialog::getInt(nullptr, "", "");
    int input;
    std::cin >> input;

    return input;
}


int InteractingController::GetSelectedCardFromBattleField(const QVector<int>& filter)
{
    throw 0;
}


void InteractingController::GetSelectedUnitDeployLocation(QString& deployBattleLine, int& deployIndex)
{
    std::cout << "You are now deploying the card to the battlefield, please input two integers" << std::endl;
    std::cout << "the first int represent the battle line, as following:" << std::endl;
    std::cout << "1 - AlliedMelee\n2 - AlliedRanged\n3 - AlliedSiege\n";
    std::cout << "4 - EnemyMelee\n5 - EnemyRanged\n6 - EnemySiege\n";
    std::cout << "the second int represent the index of the insertion\n";

    //    int first  = QInputDialog::getInt(nullptr, "", "");
    //    int second = QInputDialog::getInt(nullptr, "", "");

    int first;
    int second;
    std::cin >> first;
    std::cin >> second;

    switch (first)
    {
    case 1:
    {
        deployBattleLine = "AlliedMelee";
        break;
    }
    case 2:
    {
        deployBattleLine = "AlliedRanged";
        break;
    }
    case 3:
    {
        deployBattleLine = "AlliedSiege";
        break;
    }
    case 4:
    {
        deployBattleLine = "EnemyMelee";
        break;
    }
    case 5:
    {
        deployBattleLine = "EnemyRanged";
        break;
    }
    case 6:
    {
        deployBattleLine = "EnemySiege";
        break;
    }
    default:break;
    }

    deployIndex = second;
}


QString InteractingController::GetSelectedEffectDeployBattleLine()
{
    std::cout << "You are now deploying the effect to a battle line, please input a integer" << std::endl;
    std::cout << "the int represent the battle line, as following:" << std::endl;
    std::cout << "1 - AlliedMelee\n2 - AlliedRanged\n3 - AlliedSiege\n";
    std::cout << "4 - EnemyMelee\n5 - EnemyRanged\n6 - EnemySiege\n";

    //    int input = QInputDialog::getInt(nullptr, "", "");
    int input;
    std::cin >> input;
    switch (input)
    {
    case 1:return "AlliedMelee";
    case 2:return "AlliedRanged";
    case 3:return "AlliedSiege";
    case 4:return "EnemyMelee";
    case 5:return "EnemyRanged";
    case 6:return "EnemySiege";
    }
}


void InteractingController::GetGlobalSelection()
{
    std::cout << "Only to confirm, input a integer\n";
    //    int i = QInputDialog::getInt(nullptr, "", "");
    int i;
    std::cin >> i;
}


void InteractingController::UpdateBattleFieldView()
{
    std::cout << "================================\n";
    std::cout << "Enemy Hand\n";
    std::cout << "[" << Controller->GetBattleField()->GetCardContainerByName("EnemyHand")->GetCards().size()
              << " cards remained]\n";
    std::cout << "================================\n";
    std::cout << "Enemy Siege "
              << Controller->GetBattleField()->GetBattleLineByName("EnemySiege")->GetWeatherString().toStdString()
              << std::endl;
    for (const auto item:Controller->GetBattleField()->GetBattleLineByName("EnemySiege")->GetUnits())
    {
        std::cout << Controller->GetCardManager()->GetCardById(item)->ToDisplayableString().toStdString() << std::endl;
    }
    std::cout << "================================\n";
    std::cout << "Enemy Ranged "
              << Controller->GetBattleField()->GetBattleLineByName("EnemyRanged")->GetWeatherString().toStdString()
              << std::endl;
    for (const auto item:Controller->GetBattleField()->GetBattleLineByName("EnemyRanged")->GetUnits())
    {
        std::cout << Controller->GetCardManager()->GetCardById(item)->ToDisplayableString().toStdString() << std::endl;
    }
    std::cout << "================================\n";
    std::cout << "Enemy Melee "
              << Controller->GetBattleField()->GetBattleLineByName("EnemyMelee")->GetWeatherString().toStdString()
              << std::endl;
    for (const auto item:Controller->GetBattleField()->GetBattleLineByName("EnemyMelee")->GetUnits())
    {
        std::cout << Controller->GetCardManager()->GetCardById(item)->ToDisplayableString().toStdString() << std::endl;
    }
    std::cout << "================================\n";
    std::cout << "Allied Melee "
              << Controller->GetBattleField()->GetBattleLineByName("AlliedMelee")->GetWeatherString().toStdString()
              << std::endl;
    for (const auto item:Controller->GetBattleField()->GetBattleLineByName("AlliedMelee")->GetUnits())
    {
        std::cout << Controller->GetCardManager()->GetCardById(item)->ToDisplayableString().toStdString() << std::endl;
    }
    std::cout << "================================\n";
    std::cout << "Allied Ranged "
              << Controller->GetBattleField()->GetBattleLineByName("AlliedRanged")->GetWeatherString().toStdString()
              << std::endl;
    for (const auto item:Controller->GetBattleField()->GetBattleLineByName("AlliedRanged")->GetUnits())
    {
        std::cout << Controller->GetCardManager()->GetCardById(item)->ToDisplayableString().toStdString() << std::endl;
    }
    std::cout << "================================\n";
    std::cout << "Allied Siege "
              << Controller->GetBattleField()->GetBattleLineByName("AlliedSiege")->GetWeatherString().toStdString()
              << std::endl;
    for (const auto item:Controller->GetBattleField()->GetBattleLineByName("AlliedSiege")->GetUnits())
    {
        std::cout << Controller->GetCardManager()->GetCardById(item)->ToDisplayableString().toStdString() << std::endl;
    }
    std::cout << "================================\n";
    std::cout << "Allied Hand\n";
    for (const auto item:Controller->GetBattleField()->GetCardContainerByName("AlliedHand")->GetCards())
    {
        std::cout << Controller->GetCardManager()->GetCardById(item)->ToDisplayableString().toStdString() << std::endl;
    }
    std::cout << "================================\n";
}


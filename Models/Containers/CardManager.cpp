//
// Created on 2017/09/03 at 18:27.
//

#include "CardManager.hpp"


Card *CardManager::GetCardById(int cardId)
{
    for (const auto& i:CardsOnBoard)
    {
        if (i->GetCardId() == cardId)
        {
            return i;
        }
    }

    throw 349534;
}


void CardManager::RegisterCard(Card *card)
{
    CardsOnBoard.insert(0, card);
}


CardManager::CardManager()
{
    CardsOnBoard = QVector<Card *>();
}


QString CardManager::ToString()
{
    auto list = QStringList();

    for (const auto item:CardsOnBoard)
    {
        list.append(item->ToString());
    }

    return list.join('%');
}


void CardManager::UpdateFromString(const QString& source, GameController *gameController)
{
    auto list = source.split('%');
    for (const auto& cardInfo:list)
    {
        auto infoList = cardInfo.split('_');
        auto id       = infoList[0].toInt();

        if (IsCardManaged(id))
        {
            GetCardById(id)->UpdateFromString(cardInfo);
        }
        else
        {
            auto cardName = infoList[1];
            auto card     = Card::SpawnCardByName(cardName, gameController);
            card->UpdateFromString(cardInfo);
            CardsOnBoard.append(card);
        }
    }
}


bool CardManager::IsCardManaged(int cardId)
{
    for (const auto& item:CardsOnBoard)
    {
        if (item->GetCardId() == cardId)
        {
            return true;
        }
    }
    return false;
}

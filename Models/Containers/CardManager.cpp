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

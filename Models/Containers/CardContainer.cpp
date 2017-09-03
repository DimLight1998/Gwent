//
// Created on 2017/09/03 at 16:12.
//

#include "CardContainer.hpp"


const QVector<int>& CardContainer::GetCards() const
{
    return Cards;
}


void CardContainer::RemoveCardOfId(int id)
{
    try
    {
        for (int i = 0; i < Cards.size(); i++)
        {
            if (Cards[i] == id)
            {
                Cards.remove(i);
                return;
            }
        }
    }
    catch (...)
    {
        throw 849532;
    }
}


bool CardContainer::IsCardContainerContainingCard(int id)
{
    for (auto& i:Cards)
    {
        if (i == id)
        {
            return true;
        }
    }

    return false;
}

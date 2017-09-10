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


void CardContainer::InsertCard(int cardId, int index)
{
    if (index < 0 || index > Cards.size())
    {
        throw 233333;
    }

    Cards.insert(index, cardId);
}


CardContainer::CardContainer()
{
    Cards = QVector<int>();
}


void CardContainer::ClearCardContainer()
{
    Cards.clear();
}


QString CardContainer::ToString()
{
    auto list = QStringList();

    for (const auto item:Cards)
    {
        list.append(QString::number(item));
    }

    return list.join('%');
}


void CardContainer::UpdateFromString(const QString& source)
{
    auto list = source.split('%');
    Cards.clear();
    for (const auto& item:list)
    {
        Cards.append(item.toInt());
    }
}

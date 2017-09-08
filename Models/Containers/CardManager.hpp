//
// Created on 2017/09/03 at 18:27.
//

#ifndef GWENT_CARDMANAGER_HPP
#define GWENT_CARDMANAGER_HPP

#include <QtCore/QVector>
#include "../Card/Card.hpp"


class Card;


class CardManager
{
protected:
    QVector<Card *> CardsOnBoard;
public:
    /// \brief get a pointer to the card by its id
    /// \param cardId id of the card
    /// \return pointer to the card
    /// \throw 349534 if cardId incorrect
    Card *GetCardById(int cardId);
    CardManager();

    /// \brief insert a card to the container and it will be managed
    /// \param card pointer to the card
    void RegisterCard(Card *card);
};


#endif //GWENT_CARDMANAGER_HPP

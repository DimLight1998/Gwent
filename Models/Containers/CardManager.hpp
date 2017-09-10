//
// Created on 2017/09/03 at 18:27.
//

#ifndef GWENT_CARDMANAGER_HPP
#define GWENT_CARDMANAGER_HPP

#include <QtCore/QVector>
#include "../Card/Card.hpp"


class GameController;


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

    /// \brief convert all the cards in manage system to string to manage, with separator %
    /// \return a string representing all the cards for synchronization
    QString ToString();

    /// \brief update the card manager from the string
    /// \param source string defining the manager, in format
    /// \param gameController pointer to the game controller
    /// 7_EarthElemental_6_0_0_0%
    /// 6_EarthElemental_6_0_0_0%
    /// 5_Archgriffin_8_0_0_0%
    /// 4_VranWarrior_5_0_0_0%
    /// 3_VranWarrior_5_0_0_0%
    /// 2_CelaenoHarpy_5_0_0_0%
    /// 1_CelaenoHarpy_5_0_0_0"
    void UpdateFromString(const QString& source, GameController *gameController);

protected:
    bool IsCardManaged(int cardId);
};


#endif //GWENT_CARDMANAGER_HPP

//
// Created on 2017/09/05 at 09:58.
//

#ifndef GWENT_INTERACTINGCONTROLLER_HPP
#define GWENT_INTERACTINGCONTROLLER_HPP

#include "../Models/Meta/CardMeta.hpp"
#include <QVector>


class GameController;


class GamePlayingState;


class InteractingController
{
public:
    GameController *GetController() const;
    void SetController(GameController *Controller);

    /// \brief get selected card from existing cards, like select one card from the deck
    /// \param existingCardsId the vector of cards chosen from
    /// \return id of the chosen card
    /// \example
    /// \code
    /// QVector<int> vec;
    /// for(auto i: deck)
    /// {
    ///     vec.append(i);
    /// }
    ///
    /// auto ret = GetSelectedCardFromExistingCards(vec);
    /// \endcode
    /// now we have what the player choose
    int GetSelectedCardFromExistingCards(const QVector<int>& existingCardsId);

    InteractingController(GameController *Controller);

    /// \brief get selected card from existing cards, and you can abdicate the operation
    /// \param existingCardsId the vector of cards chosen from
    /// \return id of the chosen card, if the operation is abdicated, return -1
    int GetSelectedCardFromExistingCardsAbdicable(const QVector<int>& existingCardsId);

    /// \brief everyround, get the input of the player
    /// \param [out] abdicate true if the player abdicate the round, otherwise false
    /// \param [out] selectedCardId id of the card player choose to deploy, if abdicate, return -1
    void GetRoundInput(bool& abdicate, int& selectedCardId);

    /// \brief get selected card from non-existing cards, like select one from three weather (Dagon)
    /// \param spawningCardsMeta the vector of cards chosen from
    /// \return CardMeta of the chosen card
    /// \example
    /// \code
    /// QVector<CardMeta> cardMeta = QVector<CardMeta>
    /// ({CardMeta::GetMetaByCardName("BitingFrost"), CardMeta::GetMetaByCardName("ImpenetrableFog")});
    /// auto selected = GetSelectedCardFromSpanningCards(cardMeta);
    /// for(auto i:cardMeta)
    /// {
    ///     delete i;
    /// }
    ///
    /// \endcode
    /// now we have what the player choose
    CardMeta GetSelectedCardFromSpanningCards(const QVector<CardMeta *>& spawningCardsMeta);

    /// \brief wait until the player made a global selection
    void GetGlobalSelection();

    /// \brief get an selected card from the battle field
    /// \return id of the card
    int GetSelectedCardFromBattleField();

    /// \brief wait until player choose a valid location to deploy a unit
    /// \param [out] deployBattleLine battle line of deployment, in format (Enemy|Allied)(Melee|Siege|Ranged)
    /// \param [out] deployIndex index of the deployment
    void GetSelectedUnitDeployLocation(QString& deployBattleLine, int& deployIndex);

    /// \brief wait until player choose a valid line to deploy a battle line
    /// \return battle line of deployment, in format (Enemy|Allied)(Melee|Siege|Ranged)
    QString GetSelectedEffectDeployBattleLine();

    /// \brief update the view of the battle field
    void UpdateBattleField();

    void SetPlayingState(GamePlayingState *PlayingState);

protected:
    GameController   *Controller;
    GamePlayingState *PlayingState;
};


#endif //GWENT_INTERACTINGCONTROLLER_HPP

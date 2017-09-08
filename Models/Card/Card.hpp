//
// Created on 2017/09/03 at 15:38.
//

#ifndef GWENT_CARD_HPP
#define GWENT_CARD_HPP

#include <QtCore/QObject>
#include "../Meta/CardMeta.hpp"
#include "../../Controllers/GameController.hpp"


class GameController;


class Card : public QObject
{
Q_OBJECT
public:
    Card(GameController *gameController);

    /// \brief triggered when the card is deployed
    virtual void OnDeploy();

    /// \brief triggered when the card is destroyed
    /// \note This function will handle moving the card to the grave and trigger its death wish
    virtual void OnDestroy();

    /// \bried triggered when the death wish of the unit is triggered
    /// \note The reason why I use this function is because some unit can trigger death wish but they don't need to die
    virtual void OnDeathWish();

    /// \brief will handle the deletion of CardMetaInfo
    virtual ~Card();

    /// \brief get a pointer to the card by its name
    /// \param name name of the card
    /// \return pointer to the card
    /// \note you only have a instance of the card and you should add it to the card system,
    /// maybe you want to use GameController::SpanCard
    static Card *SpanCardByName(const QString& name, GameController *gameController);

    virtual void RoundUpdate();
protected:
    CardMeta *CardMetaInfo; ///< stores meta-info of the card, not for sharing

    int CardId;

    GameController *GlobalGameController;
public:
    CardMeta *GetCardMetaInfo() const;
    void SetCardMetaInfo(CardMeta *CardMetaInfo);
    int GetCardId() const;
    void SetCardId(int CardId);

    virtual QString ToString();
};


#endif //GWENT_CARD_HPP

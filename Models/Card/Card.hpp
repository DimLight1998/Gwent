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
    static Card *SpawnCardByName(const QString& name, GameController *gameController);

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

    /// \brief convert the card to a string which can be displayed on the console,
    /// this should be used for console-gwent
    /// \return a string representing the card
    virtual QString ToDisplayableString();

    /// \brief convert the card to a string which can be transfered throw network, with separator |
    /// \return a string representing the card
    virtual QString ToString();

    /// \brief update the card from a string
    /// \param source the string describing the card
    virtual void UpdateFromString(const QString& source) = 0;

    QString GetFactionString();

    virtual void OnWeatherChangedHandler(
        const QString& battleLineName, BattleLine::WeatherEnum originalWeather, BattleLine::WeatherEnum newWeather
    );
    virtual void OnOtherCardDeployHandler(int cardId);
    virtual void OnRoundUpdateHandler();
    virtual void OnOtherUnitSwallowedHandler(int cardId);
};


#endif //GWENT_CARD_HPP

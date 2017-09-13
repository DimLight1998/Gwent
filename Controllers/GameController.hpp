//
// Created on 2017/09/03 at 17:27.
//

#ifndef GWENT_GAMECONTROLLER_HPP
#define GWENT_GAMECONTROLLER_HPP

#include <QEventLoop>

#include "../Models/Containers/BattleField.hpp"
#include "../Models/Containers/BattleLine.hpp"
#include "../Models/Containers/CardManager.hpp"
#include "InteractingController.hpp"
#include "../Models/Containers/CardGroup.hpp"
#include "Network/Client.hpp"
#include "InteractingController.hpp"


class InteractingController;


class CardManager;


class BattleField;


class GameController : public Client
{
Q_OBJECT

private:
    BattleField           *_battleField = nullptr;
    CardManager           *_cardManager = nullptr;

public:
    GameController();
    /// \brief this function can deploy a unit to a specific battle line,
    /// then trigger its OnDeploy function
    /// \param cardId id of the card
    /// \param battleLineName the battle line it will be deployed to, format: (Enemy|Allied)(Melee|Ranged|Siege)
    /// \param index the index of the battle line, starting from 0
    /// \note the function won't check if the card can be deployed, it just does what is told
    void DeployUnitToBattleLine(int cardId, const QString& battleLineName, int index);

    /// \brief set weather to a specific battle line
    /// \param battleLineName the battle line weather will be set at, format: (Enemy|Allied)(Melee|Ranged|Siege)
    /// \param weather the weather, can be None
    void SetWeatherToBattleLine(const QString& battleLineName, BattleLine::WeatherEnum weather);

    /// \brief try to deploy a unit from a specific container to a specific battle line
    /// \param cardName name of the card
    /// \param containerName name of the container, in format: (Enemy|Allied)(Hand|Deck|Grave|Discard)
    /// \param battleLineName name of the battle line, in format: (Enemy|Allied)(Melee|Ranged|Siege)
    /// \param index index of the insertion
    /// \return true if success, else false
    /// \throw 4593453 if name incorrect
    bool DeployUnitFromContainerToBattleLine
        (const QString& cardName, const QString& containerName, const QString& battleLineName, int index);
protected:
    void HandleMessage(const QString& message) override;
public:

    /// \brief move a card from a specific battle line to another specific battle line
    /// \param id id of the card to be moved
    /// \param sourceBattleLineName name of the source battle line, in format:
    /// (Enemy|Allied)(Melee|Ranged|Siege)
    /// \param destinationBattleLineName name of the destination battle line,
    /// in format: (Enemy|Allied)(Melee|Ranged|Siege)
    /// \param index index of the position of insertion
    /// \return true if success, else false
    /// \note it won't throw any exception because if the card is not in the source battle line, it will return false
    /// \note Use MoveCardFromCardsSetToCardsSet for more functionality
    bool MoveCardFromBattleLineToBattleLine
        (int id, const QString& sourceBattleLineName, const QString& destinationBattleLineName, int index);

    /// \brief This is the second most powerful moving function!
    /// It can move a card from a specific battle line or container to another specific battle line or container
    /// \param id id of the card to be moved
    /// \param sourceCardsSetName name of the source battle line or container,
    /// in format: (Enemy|Allied)(Melee|Ranged|Siege|Hand|Deck|Grave|Discard)
    /// \param destinationCardsSetName name of the destination battle line or container,
    /// in format: (Enemy|Allied)(Melee|Ranged|Siege|Hand|Deck|Grave|Discard)
    /// \param index index of the position of insertion
    /// \return true if success, else false (if you don't have card of id in source cards set, it will return false)
    bool MoveCardFromCardsSetToCardsSet
        (int id, const QString& sourceCardsSetName, const QString& destinationCardsSetName, int index);

    /// \brief This is the second most powerful moving function!
    /// It can move a card to a specific battle line or container
    /// \param id id of the card to be moved
    /// \param destinationCardsSetName name of the destination battle line or container,
    /// in format: (Enemy|Allied)(Melee|Ranged|Siege|Hand|Deck|Grave|Discard)
    /// \param index index of the position of insertion
    /// \return true if success, else false
    bool MoveCardFromCardsSetToCardsSet
        (int id, const QString& destinationCardsSetName, int index);

    /// \brief test if the unit is an enemy (the unit must on the battle field, not in grave/hand/deck)
    /// \param id id of the unit
    /// \return true if yes else no;
    bool IsThisUnitEnemy(int id);

    /// \brief test if the unit is an allied unit (the unit must on the battle field, not in grave/hand/deck)
    /// \param id id of the unit
    /// \return true if yes else no
    bool IsThisUnitAllied(int id);

    /// \brief test if the card is an enemy card (the unit can be anywhere as long as it's managed)
    /// \param id id of the card
    /// \return true if yes else no
    bool IsThisCardEnemy(int id);

    /// \brief test if the card is an allied card (the unit can be anywhere as long as it's managed)
    /// \param id id of the card
    /// \return true if yes else no
    bool IsThisCardAllied(int id);

    /// \brief test if ally has cards in hand
    /// \return true if yes, else no
    bool AllyHasCards();

    /// \brief handle the result of deploying an impenetrable fog
    /// \param battleLine
    void HandleImpenetrableFogDeployed(const QString& battleLine);

    /// \brief handle gold card deploying before it calculates its result
    void HandleGoldCardDeploying();

    /// \brief get the power of the card if swallow the card
    /// \param swallowedCardId id of the card to be swallowed
    /// \return the gain of power if swallow the card
    int GetPowerUpOfSwallowing(int swallowedCardId);

    /// \brief handle the result of some unit swallowed
    void HandleUnitSwallowed();

    /// \brief spawn a card, allocate an id for it, add it to the card management system,
    /// then add it to a battle field of container by index
    /// \param cardName name of the card
    /// \param containerOrBattleLineName name of the container,
    /// in format (Enemy|Allied)(Hand|Deck|Grave|Discard|Melee|Ranged|Siege)
    /// \param index index of insertion, if index == -1, a random index will be used
    /// \return id of the card
    int SpawnCard(const QString& cardName, const QString& containerOrBattleLineName, int index);

    /// \brief deploy the card with id and trigger its OnDeploy, no matter where is the card
    /// \note this function will let user choose a location or what
    /// \param id id of the card
    void DeployTheCardOfId(int id);

    /// \brief called to controll the game logic
    void StartGameEntry();

    /// \brief called per round to
    void HandleRoundUpdate();

    void UpdateRoundPower();

    void SynchronizeRemoteData();
    void SynchronizeRemoteDataAllySideOnly();

    QVector<int> GetBattleLineScores();
    QVector<QString> GetBattleLineWeathers();
    bool GetIsAllyTurn();

    void SetAllyCardGroup(const CardGroup& AllyCardGroup);

    BattleField *GetBattleField() const;
    CardManager *GetCardManager() const;

protected:
    /// \brief get the next allocatable id
    /// \return the next allocatable id
    /// \todo synchronize with the server
    /// \note the id is starting from 1
    int GetNextId();
public:
    InteractingController *GetInteracting() const;
    void SetInteracting(InteractingController *Interacting);
    InteractingController *Interacting  = nullptr;
protected:
    //<editor-fold desc="data used for a game">
    bool IsAllyAbdicated;
    bool IsEnemyAbdicated;
    int  AllyRoundPower;
    int  EnemyRoundPower;

    int AllyTotalScore;
    int EnemyTotalScore;

    int AllyRound1Score = 0;
    int AllyRound2Score = 0;
    int AllyRound3Score = 0;

    int EnemyRound1Score = 0;
    int EnemyRound2Score = 0;
    int EnemyRound3Score = 0;

    int PlayerNumber;

    bool IsAllyTurn;

    QString FirstMoveInfo;

    CardGroup        AllyCardGroup;
    QVector<QString> AllyCardBlackList;

    /// \brief reset the data used for a game
    void ResetGameData();

    /// \brief called per round to initialize data for game, called per round
    void InitializeRoundGameData();

    /// \brief shuffle the deck, then move the leader into your hand
    /// \note before you call the function, you should have a valid card group storing in AllyCardGroup
    void InitializeAllyCardData();

    /// \brief draw one card from the the top of the deck, then add it into your hand
    void DrawOneCard();

    /// \brief put one card back into the deck randomly, add it to black-list, then redraw a card from the deck
    /// \param originalCardId the card need to be put back
    void RedrawOneCard(int originalCardId);

    /// \brief handle redraw (interacting)
    /// \param redrawLimit how much time you can redraw most
    void HandleRedraw(int redrawLimit);

    /// \brief called before the game to set up network
    void InitializeNetwork();

    void SynchronizeLocalData(const QString& message);
    void SynchronizeRemoteDataAllyHandOnly();

    //</editor-fold>
protected:
    const int MaxCardPerSideInGame = 1 << 30; // Obviously you can't deploy 1073741824 cards in a game
    // the Id system used all integers:
    // from 1 to 1<<30: used for id for player 0
    // from 1<<30+1 to 1<<31-1: used for id for player 1
    // 0: reserved
    // -1: used for default in some cased
    // others: reserved

    QString AddressOfRemoteServer;
    quint16 PortOfRemoteServer;
public:
    void SetAddressOfRemoteServer(const QString& AddressOfRemoteServer);
    void SetPortOfRemoteServer(quint16 PortOfRemoteServer);
private:
    /// \brief hacking code goes here
    void HackBeforeStart();

signals:
    void BothSidesGetReady();
};


#endif //GWENT_GAMECONTROLLER_HPP

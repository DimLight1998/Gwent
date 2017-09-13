//
// Created on 2017/09/12 at 16:38.
//

#ifndef GWENT_GAMEPLAYINGSTATE_HPP
#define GWENT_GAMEPLAYINGSTATE_HPP

#include <QtWidgets/QPushButton>
#include <QtCore/QSignalMapper>
#include <QHBoxLayout>
#include <QMouseEvent>
#include "IState.hpp"
#include "../../Controllers/GameController.hpp"


class GameController;
namespace Ui
{
class GamePlayingState;
}

class GamePlayingState : public QWidget, public IState
{
Q_OBJECT
public:
    GamePlayingState(QWidget *parent);
    virtual ~GamePlayingState();
protected:
    Ui::GamePlayingState *GamePlayingStateUi;
    GameController       *MainGameController = nullptr;
public:
    GameController *GetMainGameController() const;
protected:

    QString ServerAddress;
    quint16 ServerPort;

    QString   SelectedCardGroupName;
    CardGroup SelectedCardGroup;

    void LoadCardGroupFromServer();

    int GetIndexByMouseAndLayout(QMouseEvent *mouseEvent, QHBoxLayout *layout);
public:
    const QString& GetServerAddress() const;
    void SetServerAddress(const QString& ServerAddress);
    quint16 GetServerPort() const;
    void SetServerPort(quint16 ServerPort);
    const QString& GetSelectedCardGroupName() const;
    void SetSelectedCardGroupName(const QString& SelectedCardGroupName);
public:
    void StartGame();
public:
    // Interacting helper

    /// \brief clear the deck
    void ClearHand();

    /// \brief clear the battle line
    void ClearBattleLine();

    /// \brief insert a card in to a deck
    /// \param faction faction of the card, in format (Enemy|Ally)
    /// \param cardId id of the card
    /// \param index index of insertion
    void InsertCardToHand(const QString& faction, int cardId, int index);

    /// \brief insert a unit in to the battle line
    /// \param battleLineName in format (Enemy|Allied)(Siege|Melee|Ranged)
    /// \param cardId id of the card
    /// \param index index of the insertion
    void InsertCardToBattleLine(const QString& battleLineName, int cardId, int index);

    void UpdateUi(
        const QVector<int>& battleLineScores,
        const QVector<QString>& battleLineWeathers,
        bool isAllyTurn
    );

public:
    bool eventFilter(QObject *watched, QEvent *event) override;

    void RefreshCardsConnections();

    QSignalMapper *SignalMapper = nullptr;

protected:
    QPushButton *EnemySiegeScoreIndicator;
    QPushButton *EnemyRangedScoreIndicator;
    QPushButton *EnemyMeleeScoreIndicator;
    QPushButton *AlliedSiegeScoreIndicator;
    QPushButton *AlliedRangedScoreIndicator;
    QPushButton *AlliedMeleeScoreIndicator;

    QPushButton *EnemySiegeIndicator;
    QPushButton *EnemyRangedIndicator;
    QPushButton *EnemyMeleeIndicator;
    QPushButton *AlliedSiegeIndicator;
    QPushButton *AlliedRangedIndicator;
    QPushButton *AlliedMeleeIndicator;

signals:
    void ClickedOnEnemySiege(int index);
    void ClickedOnEnemyRanged(int index);
    void ClickedOnEnemyMelee(int index);
    void ClickedOnAlliedMelee(int index);
    void ClickedOnAlliedRanged(int index);
    void ClickedOnAlliedSiege(int index);

    void ClickedOnAbdicateButton();
};


#endif //GWENT_GAMEPLAYINGSTATE_HPP

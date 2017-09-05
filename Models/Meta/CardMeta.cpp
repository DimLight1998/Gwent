//
// Created on 2017/09/03 at 14:06.
//

#include "CardMeta.hpp"
#include "EffectsMeta.hpp"
#include "UnitMeta.hpp"


CardMeta::CardTypeEnum CardMeta::GetCardType() const
{
    return _cardType;
}


void CardMeta::SetCardType(CardMeta::CardTypeEnum cardType)
{
    _cardType = cardType;
}


const QString& CardMeta::GetName() const
{
    return _name;
}


void CardMeta::SetName(const QString& name)
{
    _name = name;
}


const QString& CardMeta::GetDescription() const
{
    return _description;
}


void CardMeta::SetDescription(const QString& description)
{
    _description = description;
}


const QString& CardMeta::GetPictureResourcePath() const
{
    return _pictureResourcePath;
}


void CardMeta::SetPictureResourcePath(const QString& pictureResourcePath)
{
    _pictureResourcePath = pictureResourcePath;
}


CardMeta *CardMeta::GetMetaByCardName(const QString& name)
{
    //<editor-fold desc="these cards are basic">
    if (name == "FirstLight")
    {
        auto cardMeta = new EffectsMeta();
        cardMeta->SetName("FirstLight");
        cardMeta->SetCardType(CardTypeEnum::Bronze);
        cardMeta->SetDescription(
            "Spawn Clear Skies or Rally."
        );
        cardMeta->SetPictureResourcePath(""); // todo fill this
        cardMeta->SetDeployType(EffectsMeta::DeployTypeEnum::GlobalSelection);

        return cardMeta;
    }

    if (name == "BitingFrost")
    {
        auto cardMeta = new EffectsMeta();
        cardMeta->SetName("BitingFrost");
        cardMeta->SetCardType(CardTypeEnum::Bronze);
        cardMeta->SetDescription(
            "Apply Frost to a row on your opponent's side.\n"
                "Frost: Every turn, at the start of your turn, Damage the Lowest Unit on the row by 2."
        );
        cardMeta->SetPictureResourcePath("");// todo fill this
        cardMeta->SetDeployType(EffectsMeta::DeployTypeEnum::LineSelect);

        return cardMeta;
    }

    if (name == "ImpenetrableFog")
    {
        auto cardMeta = new EffectsMeta();
        cardMeta->SetName("ImpenetrableFog");
        cardMeta->SetCardType(CardTypeEnum::Bronze);
        cardMeta->SetDescription(
            "Apply Fog to a row on your opponent's side.\n"
                "Fog: Every turn, at the start of your turn, Damage the Highest Unit on the row by 2."
        );
        cardMeta->SetPictureResourcePath(""); // todo fill this
        cardMeta->SetDeployType(EffectsMeta::DeployTypeEnum::LineSelect);

        return cardMeta;
    }

    if (name == "Foglet")
    {
        auto cardMeta = new UnitMeta();
        cardMeta->SetName("Foglet");
        cardMeta->SetCardType(CardTypeEnum::Bronze);
        cardMeta->SetDescription(
            "Whenever you apply Fog to an opposing row, play a Foglet from your Deck on that row on your side."
                " If there are no Foglets in your Deck, Resurrect a Foglet on that row on your side.\n"
                "When all Fog has been cleared from the Board, Destroy all Foglets."
        );
        cardMeta->SetPictureResourcePath(""); //todo fill this
        cardMeta->SetIsLoyal(true);
        cardMeta->SetInitialPower(4);
        cardMeta->SetDeployLocation(UnitMeta::DeployLocationEnum::Any);

        return cardMeta;
    }

    if (name == "TorrentialRain")
    {
        auto cardMeta = new EffectsMeta();
        cardMeta->SetName("TorrentialRain");
        cardMeta->SetCardType(CardTypeEnum::Bronze);
        cardMeta->SetDescription(
            "Apply Rain to a row on your opponent's side.\n"
                "Rain: Every turn, at the start of your turn, Damage up to 2 random Units on the row by 1."
        );
        cardMeta->SetPictureResourcePath("");// todo fill this
        cardMeta->SetDeployType(EffectsMeta::DeployTypeEnum::LineSelect);

        return cardMeta;
    }

    if (name == "Lacerate")
    {
        auto cardMeta = new EffectsMeta();
        cardMeta->SetName("Lacerate");
        cardMeta->SetCardType(CardTypeEnum::Bronze);
        cardMeta->SetDescription(
            "Damage all Units on a row by 3."
        );
        cardMeta->SetPictureResourcePath("");// todo fill this
        cardMeta->SetDeployType(EffectsMeta::DeployTypeEnum::LineSelect);

        return cardMeta;
    }

    if (name == "CommandersHorn")
    {
        auto cardMeta = new EffectsMeta();
        cardMeta->SetName("CommandersHorn");
        cardMeta->SetCardType(CardTypeEnum::Silver);
        cardMeta->SetDescription(
            "Boost 5 adjacent Units by 4."
        );
        cardMeta->SetPictureResourcePath("");// todo fill this
        cardMeta->SetDeployType(EffectsMeta::DeployTypeEnum::TargetSelection);

        return cardMeta;
    }

    if (name == "BekkersTwistedMirror")
    {
        auto cardMeta = new EffectsMeta();
        cardMeta->SetName("BekkersTwistedMirror");
        cardMeta->SetCardType(CardTypeEnum::Silver);
        cardMeta->SetDescription(
            "Damage the Highest Unit by an amount equal to its Power,"
                " but no more than 10 (ignoring Armor) and Boost the Lowest other Unit by the same amount."
        );
        cardMeta->SetPictureResourcePath("");// todo fill this
        cardMeta->SetDeployType(EffectsMeta::DeployTypeEnum::GlobalSelection);

        return cardMeta;
    }

    if (name == "GeraltIgni")
    {
        auto cardMeta = new UnitMeta();
        cardMeta->SetName("GeraltIgni");
        cardMeta->SetCardType(CardTypeEnum::Gold);
        cardMeta->SetDescription(
            "Deploy: Destroy all the Highest Units on the opposite row if that row totals 25 or more Power."
        );
        cardMeta->SetPictureResourcePath(""); //todo fill this
        cardMeta->SetIsLoyal(true);
        cardMeta->SetInitialPower(5);
        cardMeta->SetDeployLocation(UnitMeta::DeployLocationEnum::Any);

        return cardMeta;
    }

    if (name == "Dagon")
    {
        auto cardMeta = new UnitMeta();
        cardMeta->SetName("Dagon");
        cardMeta->SetCardType(CardTypeEnum::Leader);
        cardMeta->SetDescription(
            "Doomed, Stubborn.\n"
                "Deploy: Spawn Biting Frost, Impenetrable Fog or Torrential Rain."
        );
        cardMeta->SetPictureResourcePath(""); //todo fill this
        cardMeta->SetIsLoyal(true);
        cardMeta->SetInitialPower(6);
        cardMeta->SetDeployLocation(UnitMeta::DeployLocationEnum::Any);

        return cardMeta;
    }

    if (name == "GeEls")
    {
        auto cardMeta = new UnitMeta();
        cardMeta->SetName("GeEls");
        cardMeta->SetCardType(CardTypeEnum::Gold);
        cardMeta->SetDescription(
            "Deploy: Draw the top Gold card and top Silver card from your Deck."
                " Play one and return the other to the top of your Deck."
        );
        cardMeta->SetPictureResourcePath(""); //todo fill this
        cardMeta->SetIsLoyal(true);
        cardMeta->SetInitialPower(1);
        cardMeta->SetDeployLocation(UnitMeta::DeployLocationEnum::Any);

        return cardMeta;
    }

    if (name == "CelaenoHarpy")
    {
        auto cardMeta = new UnitMeta();
        cardMeta->SetName("CelaenoHarpy");
        cardMeta->SetCardType(CardTypeEnum::Bronze);
        cardMeta->SetDescription(
            "Deploy: Spawn 2 Harpy Eggs to the left of this Unit."
        );
        cardMeta->SetPictureResourcePath(""); //todo fill this
        cardMeta->SetIsLoyal(true);
        cardMeta->SetInitialPower(5);
        cardMeta->SetDeployLocation(UnitMeta::DeployLocationEnum::Any);

        return cardMeta;
    }

    if (name == "WoodlandSpirit")
    {
        auto cardMeta = new UnitMeta();
        cardMeta->SetName("WoodlandSpirit");
        cardMeta->SetCardType(CardTypeEnum::Gold);
        cardMeta->SetDescription(
            "Deploy: Spawn 3 Rabid Wolves and apply Fog to the opposite row."
        );
        cardMeta->SetPictureResourcePath(""); //todo fill this
        cardMeta->SetIsLoyal(true);
        cardMeta->SetInitialPower(5);
        cardMeta->SetDeployLocation(UnitMeta::DeployLocationEnum::Any);

        return cardMeta;
    }

    if (name == "EarthElemental")
    {
        auto cardMeta = new UnitMeta();
        cardMeta->SetName("EarthElemental");
        cardMeta->SetCardType(CardTypeEnum::Bronze);
        cardMeta->SetDescription(
            "Deploy: Give this Unit a Shield.\n"
                "Deathwish: Spawn 2 Lesser Earth Elementals at the end of the row."
        );
        cardMeta->SetPictureResourcePath(""); //todo fill this
        cardMeta->SetIsLoyal(true);
        cardMeta->SetInitialPower(6);
        cardMeta->SetDeployLocation(UnitMeta::DeployLocationEnum::Melee);

        return cardMeta;
    }

    if (name == "CroneWeavess")
    {
        auto cardMeta = new UnitMeta();
        cardMeta->SetName("CroneWeavess");
        cardMeta->SetCardType(CardTypeEnum::Silver);
        cardMeta->SetDescription(
            "Deploy: Play Brewess and Whispess from your Deck."
        );
        cardMeta->SetPictureResourcePath(""); //todo fill this
        cardMeta->SetIsLoyal(true);
        cardMeta->SetInitialPower(6);
        cardMeta->SetDeployLocation(UnitMeta::DeployLocationEnum::Siege);

        return cardMeta;
    }

    if (name == "CroneWhispess")
    {
        auto cardMeta = new UnitMeta();
        cardMeta->SetName("CroneWhispess");
        cardMeta->SetCardType(CardTypeEnum::Silver);
        cardMeta->SetDescription(
            "Deploy: Play Brewess and Weavess from your Deck."
        );
        cardMeta->SetPictureResourcePath(""); //todo fill this
        cardMeta->SetIsLoyal(true);
        cardMeta->SetInitialPower(6);
        cardMeta->SetDeployLocation(UnitMeta::DeployLocationEnum::Siege);

        return cardMeta;
    }

    if (name == "CroneBrewess")
    {
        auto cardMeta = new UnitMeta();
        cardMeta->SetName("CroneBrewess");
        cardMeta->SetCardType(CardTypeEnum::Silver);
        cardMeta->SetDescription(
            "Deploy: Play Whispess and Weavess from your Deck."
        );
        cardMeta->SetPictureResourcePath(""); //todo fill this
        cardMeta->SetIsLoyal(true);
        cardMeta->SetInitialPower(8);
        cardMeta->SetDeployLocation(UnitMeta::DeployLocationEnum::Siege);

        return cardMeta;
    }

    if (name == "Archgriffin")
    {
        auto cardMeta = new UnitMeta();
        cardMeta->SetName("Archgriffin");
        cardMeta->SetCardType(CardTypeEnum::Bronze);
        cardMeta->SetDescription(
            "Deploy: Clear Weather from the row on your side. Move a Bronze card from one Graveyard to the other."
        );
        cardMeta->SetPictureResourcePath(""); //todo fill this
        cardMeta->SetIsLoyal(true);
        cardMeta->SetInitialPower(8);
        cardMeta->SetDeployLocation(UnitMeta::DeployLocationEnum::Any);

        return cardMeta;
    }

    if (name == "Caranthir")
    {
        auto cardMeta = new UnitMeta();
        cardMeta->SetName("Caranthir");
        cardMeta->SetCardType(CardTypeEnum::Gold);
        cardMeta->SetDescription(
            "Deploy: Move an Enemy to this row on its side and apply Frost to that row."
        );
        cardMeta->SetPictureResourcePath(""); //todo fill this
        cardMeta->SetIsLoyal(true);
        cardMeta->SetInitialPower(8);
        cardMeta->SetDeployLocation(UnitMeta::DeployLocationEnum::Any);

        return cardMeta;
    }

    if (name == "Frightener")
    {
        auto cardMeta = new UnitMeta();
        cardMeta->SetName("Frightener");
        cardMeta->SetCardType(CardTypeEnum::Silver);
        cardMeta->SetDescription(
            "Doomed.\n"
                "Deploy: Move a Unit on another row on this side to this row. Draw the top card from your Deck."
        );
        cardMeta->SetPictureResourcePath(""); //todo fill this
        cardMeta->SetIsLoyal(false);
        cardMeta->SetInitialPower(12);
        cardMeta->SetDeployLocation(UnitMeta::DeployLocationEnum::Any);

        return cardMeta;
    }

    if (name == "UnseenElder")
    {
        auto cardMeta = new UnitMeta();
        cardMeta->SetName("UnseenElder");
        cardMeta->SetCardType(CardTypeEnum::Leader);
        cardMeta->SetDescription(
            "Doomed, Stubborn.\n"
                "Deploy: Consume an Ally, but Strengthen instead of Boosting. Repeat 2 times."
        );
        cardMeta->SetPictureResourcePath(""); //todo fill this
        cardMeta->SetIsLoyal(true);
        cardMeta->SetInitialPower(5);
        cardMeta->SetDeployLocation(UnitMeta::DeployLocationEnum::Any);

        return cardMeta;
    }

    if (name == "Arachas")
    {
        auto cardMeta = new UnitMeta();
        cardMeta->SetName("Arachas");
        cardMeta->SetCardType(CardTypeEnum::Bronze);
        cardMeta->SetDescription(
            "Deploy: Play all Arachasae from your Deck."
        );
        cardMeta->SetPictureResourcePath(""); //todo fill this
        cardMeta->SetIsLoyal(true);
        cardMeta->SetInitialPower(3);
        cardMeta->SetDeployLocation(UnitMeta::DeployLocationEnum::Ranged);

        return cardMeta;
    }

    if (name == "ArachasBehemoth")
    {
        auto cardMeta = new UnitMeta();
        cardMeta->SetName("ArachasBehemoth");
        cardMeta->SetCardType(CardTypeEnum::Bronze);
        cardMeta->SetDescription(
            "Whenever an Ally Consumes a card, "
                "Spawn an Arachas Hatchling on a random row and Damage self by 1 (ignoring Armor).\n"
                "Deploy: Gain 2 Armor."
        );
        cardMeta->SetPictureResourcePath(""); //todo fill this
        cardMeta->SetIsLoyal(true);
        cardMeta->SetInitialPower(6);
        cardMeta->SetDeployLocation(UnitMeta::DeployLocationEnum::Siege);

        return cardMeta;
    }

    if (name == "VranWarrior")
    {
        auto cardMeta = new UnitMeta();
        cardMeta->SetName("VranWarrior");
        cardMeta->SetCardType(CardTypeEnum::Bronze);
        cardMeta->SetDescription(
            "Deploy: Consume the Unit to the right.\n"
                "Every 2 turns, at the start of your turn, Consume the Unit to the right."
        );
        cardMeta->SetPictureResourcePath(""); //todo fill this
        cardMeta->SetIsLoyal(true);
        cardMeta->SetInitialPower(5);
        cardMeta->SetDeployLocation(UnitMeta::DeployLocationEnum::Any);

        return cardMeta;
    }

    if (name == "ThunderboltPotion")
    {
        auto cardMeta = new EffectsMeta();
        cardMeta->SetName("ThunderboltPotion");
        cardMeta->SetCardType(CardTypeEnum::Bronze);
        cardMeta->SetDescription(
            "Add 2 Armor to 3 adjacent Units and Boost them by 3."
        );
        cardMeta->SetPictureResourcePath("");// todo fill this
        cardMeta->SetDeployType(EffectsMeta::DeployTypeEnum::TargetSelection);

        return cardMeta;
    }

    if (name == "Roach")
    {
        auto cardMeta = new UnitMeta();
        cardMeta->SetName("Roach");
        cardMeta->SetCardType(CardTypeEnum::Silver);
        cardMeta->SetDescription(
            "Whenever you play a Gold card from your Hand (note: does not include Leaders),"
                " play Roach from your Deck on a random row before that card resolves."
        );
        cardMeta->SetPictureResourcePath(""); //todo fill this
        cardMeta->SetIsLoyal(true);
        cardMeta->SetInitialPower(4);
        cardMeta->SetDeployLocation(UnitMeta::DeployLocationEnum::Any);

        return cardMeta;
    }

    if (name == "WildHuntRider")
    {
        auto cardMeta = new UnitMeta();
        cardMeta->SetName("WildHuntRider");
        cardMeta->SetCardType(CardTypeEnum::Bronze);
        cardMeta->SetDescription(
            "Increase by 1 the Damage dealt by Frost on the opposite row."
        );
        cardMeta->SetPictureResourcePath(""); //todo fill this
        cardMeta->SetIsLoyal(true);
        cardMeta->SetInitialPower(8);
        cardMeta->SetDeployLocation(UnitMeta::DeployLocationEnum::Any);

        return cardMeta;
    }
    //</editor-fold>

    //<editor-fold desc="these units are spawned">
    if (name == "HarpyEgg")
    {
        auto cardMeta = new UnitMeta();
        cardMeta->SetName("HarpyEgg");
        cardMeta->SetCardType(CardTypeEnum::Bronze);
        cardMeta->SetDescription(
            "Doomed.\n"
                "When Consumed by another Unit, Boost that Unit by an additional 5.\n"
                "Deathwish: Spawn a Harpy Hatchling on a random row."
        );
        cardMeta->SetPictureResourcePath(""); //todo fill this
        cardMeta->SetIsLoyal(true);
        cardMeta->SetInitialPower(1);
        cardMeta->SetDeployLocation(UnitMeta::DeployLocationEnum::Any);

        return cardMeta;
    }

    if (name == "HarpyHatchling")
    {
        auto cardMeta = new UnitMeta();
        cardMeta->SetName("HarpyHatchling");
        cardMeta->SetCardType(CardTypeEnum::Bronze);
        cardMeta->SetDescription(
            "Doomed."
        );
        cardMeta->SetPictureResourcePath(""); //todo fill this
        cardMeta->SetIsLoyal(true);
        cardMeta->SetInitialPower(1);
        cardMeta->SetDeployLocation(UnitMeta::DeployLocationEnum::Any);

        return cardMeta;
    }

    if (name == "RabidWolf")
    {
        auto cardMeta = new UnitMeta();
        cardMeta->SetName("RabidWolf");
        cardMeta->SetCardType(CardTypeEnum::Bronze);
        cardMeta->SetDescription(
            "Doomed."
        );
        cardMeta->SetPictureResourcePath(""); //todo fill this
        cardMeta->SetIsLoyal(true);
        cardMeta->SetInitialPower(1);
        cardMeta->SetDeployLocation(UnitMeta::DeployLocationEnum::Melee);

        return cardMeta;
    }

    if (name == "LesserEarthElemental")
    {
        auto cardMeta = new UnitMeta();
        cardMeta->SetName("LesserEarthElemental");
        cardMeta->SetCardType(CardTypeEnum::Bronze);
        cardMeta->SetDescription(
            "Doomed."
        );
        cardMeta->SetPictureResourcePath(""); //todo fill this
        cardMeta->SetIsLoyal(true);
        cardMeta->SetInitialPower(2);
        cardMeta->SetDeployLocation(UnitMeta::DeployLocationEnum::Melee);

        return cardMeta;
    }

    if (name == "ArachasHatchling")
    {
        auto cardMeta = new UnitMeta();
        cardMeta->SetName("ArachasHatchling");
        cardMeta->SetCardType(CardTypeEnum::Bronze);
        cardMeta->SetDescription(
            "Doomed.\n"
                "Deploy: Play all Arachasae from your Deck."
        );
        cardMeta->SetPictureResourcePath(""); //todo fill this
        cardMeta->SetIsLoyal(true);
        cardMeta->SetInitialPower(3);
        cardMeta->SetDeployLocation(UnitMeta::DeployLocationEnum::Any);

        return cardMeta;
    }

    //</editor-fold>

    //<editor-fold desc="these effects are spawned">
    if (name == "ClearSkies")
    {
        auto cardMeta = new EffectsMeta();
        cardMeta->SetName("ClearSkies");
        cardMeta->SetCardType(CardTypeEnum::Bronze);
        cardMeta->SetDescription(
            "Doomed. Clear all Weather from your side."
        );
        cardMeta->SetPictureResourcePath(""); // todo fill this
        cardMeta->SetDeployType(EffectsMeta::DeployTypeEnum::GlobalSelection);

        return cardMeta;
    }

    if (name == "Rally")
    {
        auto cardMeta = new EffectsMeta();
        cardMeta->SetName("Rally");
        cardMeta->SetCardType(CardTypeEnum::Bronze);
        cardMeta->SetDescription(
            "Doomed. Play a random Bronze Unit from your Deck."
        );
        cardMeta->SetPictureResourcePath(""); // todo fill this
        cardMeta->SetDeployType(EffectsMeta::DeployTypeEnum::GlobalSelection);

        return cardMeta;
    }
    //</editor-fold>

    throw 263784;
}


CardMeta::~CardMeta()
{
}

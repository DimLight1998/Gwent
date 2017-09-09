//
// Created on 2017/09/03 at 15:38.
//

#include "Card.hpp"

#include "../Assets/Effects/BekkersTwistedMirror.hpp"
#include "../Assets/Effects/BitingFrost.hpp"
#include "../Assets/Effects/ClearSkies.hpp"
#include "../Assets/Effects/CommandersHorn.hpp"
#include "../Assets/Effects/FirstLight.hpp"
#include "../Assets/Effects/ImpenetrableFog.hpp"
#include "../Assets/Effects/Lacerate.hpp"
#include "../Assets/Effects/Rally.hpp"
#include "../Assets/Effects/ThunderboltPotion.hpp"
#include "../Assets/Effects/TorrentialRain.hpp"
#include "../Assets/Units/Arachas.hpp"
#include "../Assets/Units/ArachasBehemoth.hpp"
#include "../Assets/Units/ArachasHatchling.hpp"
#include "../Assets/Units/Archgriffin.hpp"
#include "../Assets/Units/Caranthir.hpp"
#include "../Assets/Units/CelaenoHarpy.hpp"
#include "../Assets/Units/CroneBrewess.hpp"
#include "../Assets/Units/CroneWeavess.hpp"
#include "../Assets/Units/CroneWhispess.hpp"
#include "../Assets/Units/Dagon.hpp"
#include "../Assets/Units/EarthElemental.hpp"
#include "../Assets/Units/Foglet.hpp"
#include "../Assets/Units/Frightener.hpp"
#include "../Assets/Units/GeEls.hpp"
#include "../Assets/Units/GeraltIgni.hpp"
#include "../Assets/Units/HarpyEgg.hpp"
#include "../Assets/Units/HarpyHatchling.hpp"
#include "../Assets/Units/LesserEarthElemental.hpp"
#include "../Assets/Units/RabidWolf.hpp"
#include "../Assets/Units/Roach.hpp"
#include "../Assets/Units/UnseenElder.hpp"
#include "../Assets/Units/VranWarrior.hpp"
#include "../Assets/Units/WildHuntRider.hpp"
#include "../Assets/Units/WoodlandSpirit.hpp"


CardMeta *Card::GetCardMetaInfo() const
{
    return CardMetaInfo;
}


void Card::SetCardMetaInfo(CardMeta *CardMetaInfo)
{
    Card::CardMetaInfo = CardMetaInfo;
}


int Card::GetCardId() const
{
    return CardId;
}


void Card::SetCardId(int CardId)
{
    Card::CardId = CardId;
}


Card::~Card()
{
    delete CardMetaInfo;
}


Card *Card::SpanCardByName(const QString& name, GameController *gameController)
{
    if (name == "FirstLight")
    { return new FirstLight(gameController); }
    if (name == "BitingFrost")
    { return new BitingFrost(gameController); }
    if (name == "ImpenetrableFog")
    { return new ImpenetrableFog(gameController); }
    if (name == "Foglet")
    { return new Foglet(gameController); }
    if (name == "TorrentialRain")
    { return new TorrentialRain(gameController); }
    if (name == "Lacerate")
    { return new Lacerate(gameController); }
    if (name == "CommandersHorn")
    { return new CommandersHorn(gameController); }
    if (name == "BekkersTwistedMirror")
    { return new BekkersTwistedMirror(gameController); }
    if (name == "GeraltIgni")
    { return new GeraltIgni(gameController); }
    if (name == "Dagon")
    { return new Dagon(gameController); }
    if (name == "GeEls")
    { return new GeEls(gameController); }
    if (name == "CelaenoHarpy")
    { return new CelaenoHarpy(gameController); }
    if (name == "WoodlandSpirit")
    { return new WoodlandSpirit(gameController); }
    if (name == "EarthElemental")
    { return new EarthElemental(gameController); }
    if (name == "CroneWeavess")
    { return new CroneWeavess(gameController); }
    if (name == "CroneWhispess")
    { return new CroneWhispess(gameController); }
    if (name == "CroneBrewess")
    { return new CroneBrewess(gameController); }
    if (name == "Archgriffin")
    { return new Archgriffin(gameController); }
    if (name == "Caranthir")
    { return new Caranthir(gameController); }
    if (name == "Frightener")
    { return new Frightener(gameController); }
    if (name == "UnseenElder")
    { return new UnseenElder(gameController); }
    if (name == "Arachas")
    { return new Arachas(gameController); }
    if (name == "ArachasBehemoth")
    { return new ArachasBehemoth(gameController); }
    if (name == "VranWarrior")
    { return new VranWarrior(gameController); }
    if (name == "ThunderboltPotion")
    { return new ThunderboltPotion(gameController); }
    if (name == "Roach")
    { return new Roach(gameController); }
    if (name == "WildHuntRider")
    { return new WildHuntRider(gameController); }
    if (name == "HarpyEgg")
    { return new HarpyEgg(gameController); }
    if (name == "HarpyHatchling")
    { return new HarpyHatchling(gameController); }
    if (name == "RabidWolf")
    { return new RabidWolf(gameController); }
    if (name == "LesserEarthElemental")
    { return new LesserEarthElemental(gameController); }
    if (name == "ArachasHatchling")
    { return new ArachasHatchling(gameController); }
    if (name == "ClearSkies")
    { return new ClearSkies(gameController); }
    if (name == "Rally")
    { return new Rally(gameController); }
}


void Card::OnDeploy()
{
}


void Card::OnDestroy()
{
}


void Card::OnDeathWish()
{
}


void Card::RoundUpdate()
{
}


QString Card::ToString()
{
    return "";
}


Card::Card(GameController *gameController)
    : GlobalGameController(gameController)
{
}


QString Card::GetFactionString()
{
    if (GlobalGameController->IsThisCardAllied(CardId))
    {
        return "Allied";
    }
    if (GlobalGameController->IsThisCardEnemy(CardId))
    {
        return "Enemy";
    }
}

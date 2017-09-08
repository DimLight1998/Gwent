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


Card *Card::SpanCardByName(const QString& name)
{
    if (name == "FirstLight")
    { return new FirstLight(); }
    if (name == "BitingFrost")
    { return new BitingFrost(); }
    if (name == "ImpenetrableFog")
    { return new ImpenetrableFog(); }
    if (name == "Foglet")
    { return new Foglet(); }
    if (name == "TorrentialRain")
    { return new TorrentialRain(); }
    if (name == "Lacerate")
    { return new Lacerate(); }
    if (name == "CommandersHorn")
    { return new CommandersHorn(); }
    if (name == "BekkersTwistedMirror")
    { return new BekkersTwistedMirror(); }
    if (name == "GeraltIgni")
    { return new GeraltIgni(); }
    if (name == "Dagon")
    { return new Dagon(); }
    if (name == "GeEls")
    { return new GeEls(); }
    if (name == "CelaenoHarpy")
    { return new CelaenoHarpy(); }
    if (name == "WoodlandSpirit")
    { return new WoodlandSpirit(); }
    if (name == "EarthElemental")
    { return new EarthElemental(); }
    if (name == "CroneWeavess")
    { return new CroneWeavess(); }
    if (name == "CroneWhispess")
    { return new CroneWhispess(); }
    if (name == "CroneBrewess")
    { return new CroneBrewess(); }
    if (name == "Archgriffin")
    { return new Archgriffin(); }
    if (name == "Caranthir")
    { return new Caranthir(); }
    if (name == "Frightener")
    { return new Frightener(); }
    if (name == "UnseenElder")
    { return new UnseenElder(); }
    if (name == "Arachas")
    { return new Arachas(); }
    if (name == "ArachasBehemoth")
    { return new ArachasBehemoth(); }
    if (name == "VranWarrior")
    { return new VranWarrior(); }
    if (name == "ThunderboltPotion")
    { return new ThunderboltPotion(); }
    if (name == "Roach")
    { return new Roach(); }
    if (name == "WildHuntRider")
    { return new WildHuntRider(); }
    if (name == "HarpyEgg")
    { return new HarpyEgg(); }
    if (name == "HarpyHatchling")
    { return new HarpyHatchling(); }
    if (name == "RabidWolf")
    { return new RabidWolf(); }
    if (name == "LesserEarthElemental")
    { return new LesserEarthElemental(); }
    if (name == "ArachasHatchling")
    { return new ArachasHatchling(); }
    if (name == "ClearSkies")
    { return new ClearSkies(); }
    if (name == "Rally")
    { return new Rally(); }
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

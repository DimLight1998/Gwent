//
// Created on 2017/09/06 at 01:01.
//

#include "ArachasBehemoth.hpp"


ArachasBehemoth::ArachasBehemoth()
{
    CardMetaInfo = CardMeta::GetMetaByCardName("ArachasBehemoth");
}


void ArachasBehemoth::OnDeploy()
{
    GainArmor(2);
}

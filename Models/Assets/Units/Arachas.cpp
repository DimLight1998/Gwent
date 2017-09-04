//
// Created on 2017/09/04 at 11:01.
//

#include "Arachas.hpp"


Arachas::Arachas()
{
    CardMetaInfo = CardMeta::GetMetaByCardName("Arachas");
}


void Arachas::OnDeploy()
{
    // todo maybe incorrect
    bool success = true;

    while (success)
    {
        success = GlobalGameController->DeployCardFromContainerToBattleLine(
            "Arachas", "AlliedDeck", SelectedLine, SelectedIndex + 1
        );
    }
}

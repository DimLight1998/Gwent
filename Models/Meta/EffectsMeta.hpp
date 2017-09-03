//
// Created on 2017/09/03 at 15:33.
//

#ifndef GWENT_EFFECTSMETA_HPP
#define GWENT_EFFECTSMETA_HPP

#include "CardMeta.hpp"


class EffectsMeta : public CardMeta
{
public:
    enum class DeployTypeEnum
    {
        GlobalSelection, TargetSelection, LineSelect
    };

private:
    DeployTypeEnum _deployType;

public:
    DeployTypeEnum GetDeployType() const;
    void SetDeployType(DeployTypeEnum deployType);
};


#endif //GWENT_EFFECTSMETA_HPP

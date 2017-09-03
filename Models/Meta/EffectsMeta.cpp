//
// Created on 2017/09/03 at 15:33.
//

#include "EffectsMeta.hpp"


EffectsMeta::DeployTypeEnum EffectsMeta::GetDeployType() const
{
    return _deployType;
}


void EffectsMeta::SetDeployType(EffectsMeta::DeployTypeEnum deployType)
{
    _deployType = deployType;
}

//
// Created on 2017/09/03 at 14:11.
//

#include "UnitMeta.hpp"


int UnitMeta::GetInitialPower() const
{
    return _initialPower;
}


void UnitMeta::SetInitialPower(int initialPower)
{
    _initialPower = initialPower;
}


UnitMeta::DeployLocationEnum UnitMeta::GetDeployLocation() const
{
    return _deployLocation;
}


void UnitMeta::SetDeployLocation(UnitMeta::DeployLocationEnum deployLocation)
{
    _deployLocation = deployLocation;
}


bool UnitMeta::IsLoyal() const
{
    return _isLoyal;
}


void UnitMeta::SetIsLoyal(bool isLoyal)
{
    _isLoyal = isLoyal;
}

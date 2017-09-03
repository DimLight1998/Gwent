//
// Created on 2017/09/03 at 14:11.
//

#ifndef GWENT_UNITMETA_HPP
#define GWENT_UNITMETA_HPP

#include "CardMeta.hpp"


class UnitMeta : public CardMeta
{
public:
    enum class DeployLocationEnum
    {
        Melee, Ranged, Siege, Any
    };

private:
    DeployLocationEnum _deployLocation;
    int                _initialPower;
    bool               _isLoyal;

public:
    int GetInitialPower() const;
    void SetInitialPower(int initialPower);
    DeployLocationEnum GetDeployLocation() const;
    void SetDeployLocation(DeployLocationEnum deployLocation);
    bool IsLoyal() const;
    void SetIsLoyal(bool isLoyal);
};


#endif //GWENT_UNITMETA_HPP

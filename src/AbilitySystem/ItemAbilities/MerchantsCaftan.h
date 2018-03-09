#pragma once

#include "ItemAbility.h"

class MerchantsCaftan: public ItemAbility
{
public:
    MerchantsCaftan() = default;
    virtual ~MerchantsCaftan() = default;

    // ItemAbility interface
    virtual void init(std::shared_ptr<Scene>, std::shared_ptr<ManaGlobal> aManaModel) override;
    virtual void update(double timestep) override;

private:
    int pointsAmount = 0;
    double period = 0;
    double currentTime = 0;
};


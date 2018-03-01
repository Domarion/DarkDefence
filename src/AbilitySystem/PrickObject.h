#pragma once

#include "../AbilitySystem/AbilityAnims/AbilityAnimObject.hpp"

class PrickObject: public AbilityAnimObject
{
public:
    PrickObject(int aTimeToLive, int aDamage);

    // SceneObject interface
    bool update(double aTimeStep) override;

private:
    int damage = 0;
};

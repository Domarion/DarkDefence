#pragma once

#include "../AbilitySystem/AbilityAnims/AbilityAnimObject.hpp"

class PrickObject: public AbilityAnimObject
{
public:
    PrickObject(int aTimeToLive, int aDamage);
    virtual ~PrickObject() = default;

    // SceneObject interface
    virtual void init(int x, int y) override;

private:
    int damage;
};

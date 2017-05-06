#pragma once
#include "AbilityAnims/AbilityAnimObject.hpp"

class BlinkObject : public AbilityAnimObject
{
public:
    BlinkObject(int aTimeToLive, int aDamage);
    virtual ~BlinkObject() = default;

    // SceneObject interface
    void init(int x, int y) override;

private:
    int damage;

};

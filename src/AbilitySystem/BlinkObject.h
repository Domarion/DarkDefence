#pragma once

#include "AbilityAnims/AbilityAnimObject.hpp"

class BlinkObject : public AbilityAnimObject
{
public:
    BlinkObject(int aTimeToLive, int aDamage);

    // SceneObject interface
    void init(int x, int y) override;
    bool update(double aTimeStep) override;

private:
    int damage;
    std::list<std::shared_ptr<SceneObject>> mAffectedMobs;
};

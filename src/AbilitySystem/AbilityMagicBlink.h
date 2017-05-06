#pragma once

#include "AbilityModel.h"

class AbilityMagicBlink: public AbilityModel
{
    using SceneObjectList = std::unique_ptr<std::list<std::shared_ptr<SceneObject> > >;

public:
    AbilityMagicBlink(std::shared_ptr<ManaGlobal> aManaModel);
    virtual ~AbilityMagicBlink() = default;

    // AbilityModel interface
public:
    void init(std::shared_ptr<Scene> scenePtr) override;
    bool onReady(double timestep) override;
    bool onWorking(double timestep) override;
    int getDamage() const;
    void setDamage(int value);
    bool update(double timestep) override;
private:
    int damage;
    SceneObjectList affectedMobs;

};


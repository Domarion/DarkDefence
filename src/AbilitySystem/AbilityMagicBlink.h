#pragma once

#include "AbilityModel.h"
#include "../Input/InputHandler.h"
#include "BlinkObject.h"

class AbilityMagicBlink: public AbilityModel, public InputHandler
{
//    using SceneObjectList = std::unique_ptr<std::list<std::shared_ptr<SceneObject> > >;

public:
    AbilityMagicBlink(std::shared_ptr<ManaGlobal> aManaModel);
    virtual ~AbilityMagicBlink() = default;

    // AbilityModel interface
public:
    bool onReady(double timestep) override;
    bool onWorking(double timestep) override;
    bool onCooldown(double timestep) override;
    int getDamage() const;
    void setDamage(int value);
    bool update(double timestep) override;
    bool canPlaceObject() const override;
    // InputHandler interface
    bool onClick(Position point);

private:
    int damage;
//    SceneObjectList affectedMobs;
    std::shared_ptr<BlinkObject> someBlink;
    int coordX = 0, coordY = 0;


};


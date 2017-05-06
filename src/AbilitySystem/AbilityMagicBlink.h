#pragma once

#include "AbilityModel.h"
#include "../Input/InputHandler.h"
#include "BlinkObject.h"

class AbilityMagicBlink: public AbilityModel, public InputHandler
{
public:
    AbilityMagicBlink(std::shared_ptr<ManaGlobal> aManaModel);
    virtual ~AbilityMagicBlink() = default;

    int getDamage() const;
    void setDamage(int value);

    // AbilityModel interface
    bool onReady(double timestep) override;
    bool onWorking(double timestep) override;
    bool update(double timestep) override;
    bool canPlaceObject() const override;

    // InputHandler interface
    bool onClick(Position point) override;

private:
    int damage = 0;
    std::shared_ptr<BlinkObject> someBlink;
    int coordX = 0, coordY = 0;
};


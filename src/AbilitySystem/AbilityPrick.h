#pragma once

#include "AbilityModel.h"
#include "PrickObject.h"
#include "../Input/InputHandler.h"

class AbilityPrick: public AbilityModel, public InputHandler
{
public:
    AbilityPrick(std::shared_ptr<ManaGlobal> aManaModel);
    virtual ~AbilityPrick() = default;

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
    std::shared_ptr<PrickObject> somePrick;
    int coordX = 0, coordY = 0;
};

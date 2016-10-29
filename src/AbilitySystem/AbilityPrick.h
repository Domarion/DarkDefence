#pragma once
#include "AbilityModel.h"
#include "PrickObject.h"
#include "../Input/InputHandler.h"
class AbilityPrick: public AbilityModel, public InputHandler
{
public:
    AbilityPrick();
    virtual ~AbilityPrick();
    // AbilityModel interface
public:
    virtual void init(std::shared_ptr<Scene> scenePtr) override;
    virtual bool onReady(double timestep) override;
    virtual bool onWorking(double timestep) override;
    virtual bool onCooldown(double timestep) override;
    int getDamage() const;
    void setDamage(int value);
bool update(double timestep) override;
private:
    int damage;
    std::shared_ptr<PrickObject> somePrick;
    int coordX, coordY;
    // InputHandler interface
public:
    virtual bool onClick(SDL_Point *point) override;
};


#pragma once
#include "Mob.h"
#include "../Input/InputHandler.h"
#include "TowerFabric.hpp"
#include <functional>
#include "TowerUpgradeController.h"
class TowerUpgradeController;
class TowerFabric;
class Tower: public Mob, public InputHandler
{
    friend class TowerFabric;
public:
    void connectMethod(std::function<void(Tower*, int x, int y)> method);



    // InputHandler interface
public:
    virtual bool onClick(SDL_Point *point) override;


private:
    Tower(MobModel* model);
    virtual ~Tower();
    std::function<void(Tower*, int x, int y)> connectedMethod;
};


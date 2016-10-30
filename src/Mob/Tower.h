#pragma once
#include "Mob.h"
#include "../Input/InputHandler.h"
#include <functional>

class Tower: public Mob, public InputHandler
{

public:
    void connectMethod(std::function<void(std::shared_ptr<Tower>, int, int)> method);
    Tower(std::shared_ptr<MobModel> model, std::shared_ptr<TileMapManager> aTileMapPtr = nullptr);

    virtual ~Tower() = default;



    // InputHandler interface
public:
    virtual bool onClick(SDL_Point *point) override;


private:
    std::function<void(std::shared_ptr<Tower>, int, int)> connectedMethod;
};


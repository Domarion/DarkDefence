#pragma once

#include <functional>
#include "Mob.h"
#include "../Input/InputHandler.h"

class Tower: public Mob, public InputHandler
{
public:
    Tower(std::shared_ptr<MobModel> model, std::shared_ptr<TileMapManager> aTileMapPtr = nullptr);
    virtual ~Tower() = default;

    void connectMethod(std::function<void(std::shared_ptr<Tower>, int, int)> method);

    // InputHandler interface
public:
    virtual bool onClick(Position point) override;

private:
    std::function<void(std::shared_ptr<Tower>, int, int)> connectedMethod;
};


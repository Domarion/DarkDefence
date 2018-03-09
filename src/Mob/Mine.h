#pragma once

#include "../Grouping/SceneObject.h"
#include "MineModel.h"
#include "../AbilitySystem/DestructibleObjectEffectReceiver.h"

class Mine final: public SceneObject
{
public:
    Mine(Size aResourcePlaceSize);

    // SceneObject interface
public:

    bool update(double timestep) override;
    void finalize() override;
    std::shared_ptr<DestructibleObject> getDestructibleObject() const override;
    std::shared_ptr<EffectReceiver> getEffectReceiver() const override;

    std::shared_ptr<MineModel> getMineModel();
    void setMineModel(const std::shared_ptr<MineModel>& aNewModel);

private:
    std::shared_ptr<MineModel> model;
    std::shared_ptr<DestructibleObjectEffectReceiver> mineEffectReceiver;
    Size mResourcePlaceSize;
};


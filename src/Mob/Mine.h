#pragma once
#include "../Grouping/SceneObject.h"
#include "MineModel.h"
#include "../AbilitySystem/DestructibleObjectEffectReceiver.h"

class Mine: public SceneObject
{
public:
    Mine();

    // SceneObject interface
public:

    virtual bool update(double timestep);
    virtual void finalize();
    virtual std::shared_ptr<DestructibleObject> getDestructibleObject() const override;
    virtual std::shared_ptr<EffectReceiver> getEffectReceiver() const override;
    std::shared_ptr<MineModel> getMineModel();
    void setMineModel(std::shared_ptr<MineModel> newModel);
private:
    std::shared_ptr<MineModel> model;
    std::shared_ptr<DestructibleObjectEffectReceiver> mineEffectReceiver;
    int destructionLoss;
};


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
    virtual DestructibleObject *getDestructibleObject();
    virtual EffectReceiver *getEffectReceiver() const;
    MineModel* getMineModel();
    void setMineModel(MineModel * newModel);
private:
    MineModel* model;
    DestructibleObjectEffectReceiver* mineEffectReceiver;
};


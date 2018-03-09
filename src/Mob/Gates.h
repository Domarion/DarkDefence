#pragma once

#include "../Grouping/SceneObject.h"
#include "../AbilitySystem/DestructibleObjectEffectReceiver.h"

class Gates final: public SceneObject
{
public:
	Gates();

    std::shared_ptr<DestructibleObject> getModel();
    std::shared_ptr<DestructibleObject> getDestructibleObject() const override;
    std::shared_ptr<EffectReceiver> getEffectReceiver() const override;
    bool update(double timestep) override;
    void setModel(const std::shared_ptr<DestructibleObject>& aNewModel);
private:
    std::shared_ptr<DestructibleObject> model;
    std::shared_ptr<DestructibleObjectEffectReceiver> effectReceiver;

};


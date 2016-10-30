/*
 * Gates.h
 *
 *  Created on: 25 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include "DestructibleObject.h"
#include "../GraphicsSystem/CTexture.h"
#include "../Grouping/SceneObject.h"
#include "../AbilitySystem/DestructibleObjectEffectReceiver.h"


class Gates: public SceneObject
{
public:
	Gates();
    virtual ~Gates() = default;
    std::shared_ptr<DestructibleObject> getModel();
    virtual std::shared_ptr<DestructibleObject> getDestructibleObject() const override;
    virtual std::shared_ptr<EffectReceiver> getEffectReceiver() const override;
    virtual bool update(double timestep) override;
    void setModel(std::shared_ptr<DestructibleObject> newModel);
private:
    std::shared_ptr<DestructibleObject> model;
    std::shared_ptr<DestructibleObjectEffectReceiver> effectReceiver;

};


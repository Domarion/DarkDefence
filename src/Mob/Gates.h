/*
 * Gates.h
 *
 *  Created on: 25 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include "DestructibleObject.h"
#include "../GraphicsSystem/Sprite.h"
#include "../Grouping/SceneObject.h"
#include "../AbilitySystem/DestructibleObjectEffectReceiver.h"


class Gates: public SceneObject
{
public:
	Gates();
	virtual ~Gates();
    DestructibleObject* getModel();
    virtual DestructibleObject* getDestructibleObject() override;
    virtual bool update(double timestep) override;
	void setModel(DestructibleObject* newModel);
    EffectReceiver* getEffectReceiver() const;
private:
	DestructibleObject* model;
    DestructibleObjectEffectReceiver* effectReceiver;

};


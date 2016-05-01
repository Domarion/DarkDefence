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

class Gates: public SceneObject
{
public:
	Gates();
	virtual ~Gates();
	DestructibleObject* const getModel();
    virtual DestructibleObject* getDestructibleObject() override;
    virtual bool update(double timestep) override;
	void setModel(DestructibleObject* newModel);
private:
	DestructibleObject* model;


};


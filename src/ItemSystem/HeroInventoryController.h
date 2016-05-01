/*
 * HeroInventoryController.h
 *
 *  Created on: 28 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include "HeroInventory.h"
#include "../GraphicsSystem/UI/SlotContainer.h"
class HeroInventoryController
{
public:
	HeroInventoryController();
	virtual ~HeroInventoryController();
	void setView(SlotContainer* newView);
	SlotContainer* const getView() const;
	void setModel(HeroInventory* newModel);
	HeroInventory* const getModel() const;
	void initView();

private:
	HeroInventory* model;
	SlotContainer* view;
};



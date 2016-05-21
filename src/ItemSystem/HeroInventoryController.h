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
    SlotContainer* getView() const;
	void setModel(HeroInventory* newModel);
    HeroInventory* getModel() const;
	void initView();
    void receiveItemFromModel(string caption, int itemType);
private:
	HeroInventory* model;
	SlotContainer* view;
};



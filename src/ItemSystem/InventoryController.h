/*
 * InventoryController.h
 *
 *  Created on: 24 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include "Inventory.h"
#include "../GraphicsSystem/UI/ScrollList.h"

class InventoryController
{
public:
	InventoryController();
	virtual ~InventoryController();
	void setView(ScrollList* newView);
	ScrollList* const getView() const;
	void setModel(Inventory* newModel);
	Inventory* const getModel() const;
	void initView();
private:
	Inventory* model;
	ScrollList* view;
};


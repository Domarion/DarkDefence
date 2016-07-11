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
    ScrollList* getView() const;
	void setModel(Inventory* newModel);
    Inventory* getModel() const;
	void initView();
    void receiveItemFromModel(string caption, size_t itemType);
private:
	Inventory* model;
	ScrollList* view;
    std::shared_ptr<CFont> arial;
    SDL_Color color;
    vector<IDrawable*> buttons;

};


/*
 * ShopController.h
 *
 *  Created on: 20 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include "ShopInventory.h"
#include "../GraphicsSystem/UI/ScrollList.h"


class ShopController
{
public:
	ShopController();
	virtual ~ShopController();
	void setView(ScrollList* newView);
	ScrollList* const getView() const;
	void setModel(ShopInventory* newModel);
	ShopInventory* const getModel() const;
	void initView();
private:
	ShopInventory* model;
	ScrollList* view;
     TTF_Font* arial;
    SDL_Color color;

};

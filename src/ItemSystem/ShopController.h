/*
 * ShopController.h
 *
 *  Created on: 20 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include "ShopInventory.h"
#include "../GraphicsSystem/UI/ScrollList.h"
//#include <memory>

class ShopController
{
public:
	ShopController();
	virtual ~ShopController();
	void setView(ScrollList* newView);
    ScrollList*  getView() const;
	void setModel(ShopInventory* newModel);
    ShopInventory*  getModel() const;
	void initView();
private:
  //  vector<std::shared_ptr<ShopItemUI> > shopItems;
	ShopInventory* model;
	ScrollList* view;
    CFont arial;
    SDL_Color color;

};

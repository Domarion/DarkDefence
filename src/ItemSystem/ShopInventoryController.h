/*
 * ShopInventoryController.h
 *
 *  Created on: 19 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include "../GlobalScripts/GameModel.h"
#include "../GraphicsSystem/UI/TextButton.h"

class ShopInventoryController
{
public:
	ShopInventoryController(Inventory * const model);
	virtual ~ShopInventoryController();
private:
	Inventory* inventoryModel;
	CTexture backTexture;

};


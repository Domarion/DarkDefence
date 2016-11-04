/*
 * ShopInventory.h
 *
 *  Created on: 17 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once

#include "Inventory.h"

class ShopInventory: public Inventory
{
public:
	ShopInventory();
	virtual ~ShopInventory();
    virtual bool sendItem(size_t index) override;
};


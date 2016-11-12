/*
 * HeroInventory.h
 *
 *  Created on: 17 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once

#include "Inventory.h"
#include <list>
using std::list;
#include <string>
using std::string;

class HeroInventory: public Inventory
{
public:
    HeroInventory(int slots1 = 9);
	virtual ~HeroInventory();
    virtual bool sendItem(size_t index) override;
	virtual void receiveItem(ItemModel item) override;
	virtual void addItem(ItemModel item) override;


};


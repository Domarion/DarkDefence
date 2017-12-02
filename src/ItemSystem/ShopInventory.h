/*
 * ShopInventory.h
 *
 *  Created on: 17 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once

#include "Inventory.h"

class ShopInventory final: public Inventory
{
public:

    virtual bool sendItem(size_t aIndex) override;
};

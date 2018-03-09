#pragma once

#include "Inventory.h"

class ShopInventory final: public Inventory
{
public:
    virtual bool sendItem(size_t aIndex) override;
};

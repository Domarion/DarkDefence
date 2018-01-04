#pragma once

#include "Inventory.h"

class HeroInventory : public Inventory
{
public:

    HeroInventory() = default;
    HeroInventory(int aSlotCount = 9);

    virtual bool sendItem(size_t index) override;
	virtual void receiveItem(ItemModel item) override;
    virtual void addItem(const ItemModel& aItem) override;
};


/*
 * HeroInventory.cpp
 *
 *  Created on: 17 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "HeroInventory.h"

HeroInventory::HeroInventory(int slots1)
:Inventory()
{
    items.resize(slots1);

    for(int i = 0; i != slots1 - 1; ++i)
    {
		items[i].setItemType(static_cast<Enums::ItemTypes>(i + 1));
        items[i].setDescription("none");
    }

    items[slots1 - 1].setItemType(static_cast<Enums::ItemTypes>(slots1 - 1));
    items[slots1 - 1].setDescription("none");
}

HeroInventory::~HeroInventory()
{
}

bool HeroInventory::sendItem(size_t index)
{
    if (connectedMethod0 != nullptr && !items[index].getCaption().empty())
	{
        connectedMethod0(items[index]);
		items[index].safeClean();
		return true;
	}
	return false;
}

void HeroInventory::receiveItem(ItemModel item)
{
	if (!item.getCaption().empty())
	{
		int itemIndex = static_cast<int>(item.getItemType()) - 1;
		if (itemIndex >= 0)
		{


            if (!items[itemIndex].getCaption().empty() && connectedMethod0 != nullptr)
			{

				if (item.getItemType() != Enums::ItemTypes::CONSUMABLE || !items[++itemIndex].getCaption().empty())
					sendItem(itemIndex);
			}

			items[itemIndex] = item;
            if (connectedMethod != nullptr)
                connectedMethod(item.getCaption(), itemIndex);
		}
	}
}

void HeroInventory::addItem(ItemModel item)
{
	if (!item.getCaption().empty())
	{
		int itemIndex = static_cast<int>(item.getItemType()) - 1;
		if (itemIndex >= 0)
		{

			if (!items[itemIndex].getCaption().empty())
			{
				if (item.getItemType() != Enums::ItemTypes::CONSUMABLE || !items[++itemIndex].getCaption().empty())
					return;
			}

			items[itemIndex] = item;
		}
    }
}



/*
 * HeroInventory.cpp
 *
 *  Created on: 17 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "HeroInventory.h"

HeroInventory::HeroInventory(int slots)
:Inventory()
{
	items.resize(slots);

	for(int i = 0; i != slots - 1; ++i)
		items[i].setItemType(static_cast<Enums::ItemTypes>(i + 1));

	items[slots - 1].setItemType(static_cast<Enums::ItemTypes>(slots - 1));
	// TODO Auto-generated constructor stub

}

HeroInventory::~HeroInventory()
{
	// TODO Auto-generated destructor stub
}

bool HeroInventory::sendItem(int index)
{
	if (connectedMethod != nullptr && !items[index].getCaption().empty())
	{
		connectedMethod(items[index]);
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

			if (!items[itemIndex].getCaption().empty() && connectedMethod != nullptr)
			{
				if (item.getItemType() != Enums::ItemTypes::CONSUMABLE || !items[++itemIndex].getCaption().empty())
					sendItem(itemIndex);
			}

			items[itemIndex] = item;
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

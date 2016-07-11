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
	// TODO Auto-generated constructor stub

}

HeroInventory::~HeroInventory()
{
	// TODO Auto-generated destructor stub
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

    std::cout << " HeroInventory itemReceived" << std::endl;
	if (!item.getCaption().empty())
	{
		int itemIndex = static_cast<int>(item.getItemType()) - 1;
        std::cout << " ItemReceived index = " << itemIndex << std::endl;
		if (itemIndex >= 0)
		{


            if (!items[itemIndex].getCaption().empty() && connectedMethod0 != nullptr)
			{

				if (item.getItemType() != Enums::ItemTypes::CONSUMABLE || !items[++itemIndex].getCaption().empty())
					sendItem(itemIndex);
			}


              std::cout << " ItemReceived index = " << item.getCaption() << std::endl;
			items[itemIndex] = item;
            if (connectedMethod != nullptr)
                connectedMethod(item.getCaption(), itemIndex);
		}
	}
    else
        std::cout << " ItemReceived == 0" << std::endl;
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

list<string> HeroInventory::getItemNames()
{
    list<string> itemNames;
    for(auto ptr = items.begin(); ptr != items.end(); ++ptr)
    {
        if (!ptr->getCaption().empty())
            itemNames.push_back(ptr->getCaption());
    }
    return itemNames;
}

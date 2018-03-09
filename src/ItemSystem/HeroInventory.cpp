#include <cassert>

#include "HeroInventory.h"

HeroInventory::HeroInventory(int aSlotCount)
    : Inventory()
{
    assert(aSlotCount > 0);
    items.resize(aSlotCount);

    for(int i = 0; i != aSlotCount - 1; ++i)
    {
		items[i].setItemType(static_cast<Enums::ItemTypes>(i + 1));
        items[i].setDescription("none");
    }

    items[aSlotCount - 1].setItemType(static_cast<Enums::ItemTypes>(aSlotCount - 1));
    items[aSlotCount - 1].setDescription("none");
}


bool HeroInventory::sendItem(size_t aIndex)
{
    if (SendHandler != nullptr && !items[aIndex].getCaption().empty())
	{
        SendHandler(items[aIndex]);
        items[aIndex].safeClean();
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
            if (!items[itemIndex].getCaption().empty() && SendHandler != nullptr)
			{
				if (item.getItemType() != Enums::ItemTypes::CONSUMABLE || !items[++itemIndex].getCaption().empty())
					sendItem(itemIndex);
			}

			items[itemIndex] = item;
            if (ReceiveHandler != nullptr)
                ReceiveHandler(item.getCaption(), itemIndex);
		}
	}
}

void HeroInventory::addItem(const ItemModel& aItem)
{
    if (!aItem.getCaption().empty())
	{
        int itemIndex = static_cast<int>(aItem.getItemType()) - 1;
		if (itemIndex >= 0)
		{
			if (!items[itemIndex].getCaption().empty())
			{
                if (aItem.getItemType() != Enums::ItemTypes::CONSUMABLE || !items[++itemIndex].getCaption().empty())
					return;
			}

            items[itemIndex] = aItem;
		}
    }
}



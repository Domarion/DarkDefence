/*
 * Inventory.cpp
 *
 *  Created on: 17 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "Inventory.h"

void Inventory::ConnectModelReceiver(std::function<void(ItemModel)> method)
{
    connectedMethod0 = method;
}

const ItemModel* Inventory::getItemByName(const std::string& aItemName) const
{
    for(const auto& item : items)
        if (item.getCaption() == aItemName)
            return &item;
    return nullptr;
}

void Inventory::clearControllerReceivers()
{
    connectedMethod = nullptr;
}

bool Inventory::sendItem(size_t aItemIndex)
{
    if (aItemIndex >= items.size())
    {
        return false;
    }

    if (connectedMethod0 != nullptr && !items[aItemIndex].getCaption().empty())
	{
        connectedMethod0(items[aItemIndex]);

        if (items.size() != 1 && aItemIndex != items.size() - 1)
        {

            for(size_t i = aItemIndex; i < items.size() - 1; ++i)
                items[i] = items[i + 1];

        }

        items.pop_back();

		return true;
	}
    return false;
}

int Inventory::getItemIndexByName(const std::string& aItemName) const
{
    for(size_t i = 0; i < items.size(); ++i)
        if (items[i].getCaption() == aItemName)
            return i;
    return -1;
}

void Inventory::sendItemWithoutPriceCheck(const std::string& aItemName)
{
    size_t index = getItemIndexByName(aItemName);
    Inventory::sendItem(index);
}

void Inventory::receiveItem(ItemModel item)
{
	if (!item.getCaption().empty())
    {
		items.push_back(item);
        if (connectedMethod != nullptr)
            connectedMethod(item.getCaption(), static_cast<int>(item.getItemType()));
    }
}

void Inventory::addItem(const ItemModel& aItem)
{
    items.push_back(aItem);
}

int Inventory::getItemCount() const
{
	return items.size();
}

const ItemModel* Inventory::getItemFromIndex(size_t aItemIndex) const
{
    if (aItemIndex >= items.size())
		return nullptr;

    return &items[aItemIndex];
}

void Inventory::ConnectControllerReceiver(std::function<void (std::string, size_t)> handler)
{
    connectedMethod = handler;
}

vector<std::string> Inventory::getItemNames() const
{
    vector<std::string> itemNames;
    itemNames.reserve((items.size()));
    for(const auto& item : items)
    {
        if (!item.getCaption().empty())
            itemNames.emplace_back(item.getCaption());
    }
    return itemNames;
}

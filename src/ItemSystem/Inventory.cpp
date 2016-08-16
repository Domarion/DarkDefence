/*
 * Inventory.cpp
 *
 *  Created on: 17 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "Inventory.h"
#include <iostream>
Inventory::Inventory()
{
	// TODO Auto-generated constructor stub

}

Inventory::~Inventory()
{
	// TODO Auto-generated destructor stub
}

void Inventory::ConnectMethod(std::function<void(ItemModel)> method)
{
    connectedMethod0 = method;
}

ItemModel* Inventory::getItemByName(string name)
{
    for(size_t i = 0; i < items.size(); ++i)
        if (items[i].getCaption() == name)
            return &items[i];
    return nullptr;
}

bool Inventory::sendItem(size_t index)
{
    std::cout << "itemIndex = " << index << std::endl;
    if (index >= items.size())
        return false;
	std::cout << items[index].getCaption() << std::endl;
    if (connectedMethod0 != nullptr && !items[index].getCaption().empty())
	{
        connectedMethod0(items[index]);

        if (items.size() != 1 && index != items.size() - 1)
        {

            for(size_t i = index; i < items.size() - 1; ++i)
                items[i] = items[i + 1];

        }

        items.pop_back();

		return true;
	}
    return false;
}

int Inventory::getItemIndexByName(string name)
{
    for(size_t i = 0; i < items.size(); ++i)
        if (items[i].getCaption() == name)
            return i;
    return -1;
}

void Inventory::sendItemWithoutPriceCheck(string name)
{
    size_t index = getItemIndexByName(name);
    this->sendItem(index);
}

void Inventory::receiveItem(ItemModel item)
{
    std::cout << " Inventory itemReceived" << std::endl;
	if (!item.getCaption().empty())
    {
		items.push_back(item);
        if (connectedMethod != nullptr)
            connectedMethod(item.getCaption(), item.getItemType());
    }
}

void Inventory::addItem(ItemModel item)
{
	items.push_back(item);
}

int Inventory::getItemCount() const
{
	return items.size();
}

const ItemModel*  Inventory::getItemFromIndex(size_t index)
{
    if (index >= items.size())
		return nullptr;

    return &items[index];
}

void Inventory::ConnectReceiver(std::function<void (string, size_t)> handler)
{
    connectedMethod = handler;

}

vector<string> Inventory::getItemNames()
{
    vector<string> itemNames;
    itemNames.reserve((items.size()));
    for(auto ptr = items.begin(); ptr != items.end(); ++ptr)
    {
        if (!ptr->getCaption().empty())
            itemNames.push_back(ptr->getCaption());
    }
    return itemNames;
}

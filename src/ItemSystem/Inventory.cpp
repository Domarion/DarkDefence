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
    for(int i = 0; i < items.size(); ++i)
        if (items[i].getCaption() == name)
            return &items[i];
    return nullptr;
}

bool Inventory::sendItem(int index)
{

	std::cout << items[index].getCaption() << std::endl;
    if (connectedMethod0 != nullptr && !items[index].getCaption().empty())
	{
        connectedMethod0(items[index]);

    //	int i1 = items.size() - 1;

    //	if (index != i1)
        //	std::swap(items[index], items[i1]);

//		items.pop_back();

        if (items.size() != 1 && index != items.size() - 1)
        {

            for(int i = index; i < items.size() - 1; ++i)
                items[i] = items[i + 1];

        }

        items.pop_back();

		return true;
	}
	return false;
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

const ItemModel*  Inventory::getItemFromIndex(int index)
{
    if (index < 0 || index >= items.size())
		return nullptr;

    return &items[index];
}

void Inventory::ConnectReceiver(std::function<void (string, int)> handler)
{
    connectedMethod = handler;

}

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
	connectedMethod = method;
}

bool Inventory::sendItem(int index)
{

	std::cout << items[index].getCaption() << std::endl;
	if (connectedMethod != nullptr && !items[index].getCaption().empty())
	{
		connectedMethod(items[index]);

		int i1 = items.size() - 1;

		if (index != i1)
			std::swap(items[index], items[i1]);

		items.pop_back();
		return true;
	}
	return false;
}

void Inventory::receiveItem(ItemModel item)
{
	if (!item.getCaption().empty())
		items.push_back(item);
}

void Inventory::addItem(ItemModel item)
{
	items.push_back(item);
}

int Inventory::getItemCount() const
{
	return items.size();
}

const ItemModel* const Inventory::getItemFromIndex(int index)
{
    if (index < 0 || index >= items.size())
		return nullptr;

	return &items[index];
}

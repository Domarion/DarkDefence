/*
 * ShopInventory.cpp
 *
 *  Created on: 17 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "ShopInventory.h"
#include "../GlobalScripts/AccountModel.h"
ShopInventory::ShopInventory()
{
	// TODO Auto-generated constructor stub

}

ShopInventory::~ShopInventory()
{
	// TODO Auto-generated destructor stub
}

bool ShopInventory::sendItem(int index)
{
	if (connectedMethod == nullptr)
		return false;

	//if (AccountModel::getInstance()->PayGold(itemPrices[index]))
		return Inventory::sendItem(index);
}

void ShopInventory::addItem(ItemModel item)
{
	addItemWithPrice(item, 0);
}

void ShopInventory::addItemWithPrice(ItemModel item, int price)
{
	Inventory::addItem(item);
	itemPrices.push_back(price);
}

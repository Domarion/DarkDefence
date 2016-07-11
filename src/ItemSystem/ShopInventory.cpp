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

bool ShopInventory::sendItem(size_t index)
{
    if (connectedMethod0 == nullptr)
		return false;

    int itemPrice = items[index].getPrice();

    if (AccountModel::getInstance()->PayGold(itemPrice))
		return Inventory::sendItem(index);

    return false;
}


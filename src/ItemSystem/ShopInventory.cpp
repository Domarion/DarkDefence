/*
 * ShopInventory.cpp
 *
 *  Created on: 17 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "ShopInventory.h"
#include "../GlobalScripts/AccountModel.h"

bool ShopInventory::sendItem(size_t aIndex)
{
    if (connectedMethod0 == nullptr)
		return false;

    int itemPrice = items[aIndex].getPrice();

    if (AccountModel::getInstance()->PayGold(itemPrice))
        return Inventory::sendItem(aIndex);

    return false;
}


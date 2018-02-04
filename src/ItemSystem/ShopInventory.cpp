#include "ShopInventory.h"
#include "../GlobalScripts/AccountModel.h"

bool ShopInventory::sendItem(size_t aIndex)
{
    if (SendHandler == nullptr || aIndex >= items.size())
    {
		return false;
    }
    int itemPrice = items[aIndex].getPrice();

    if (AccountModel::getInstance()->PayGold(itemPrice))
    {
        return Inventory::sendItem(aIndex);
    }

    return false;
}


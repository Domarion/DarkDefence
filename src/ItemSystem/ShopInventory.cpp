#include "ShopInventory.h"
#include "../GlobalScripts/AccountModel.h"

bool ShopInventory::sendItem(size_t aIndex)
{
    if (SendHandler == nullptr)
    {
		return false;
    }
    // TODO Boundaries check.
    int itemPrice = items[aIndex].getPrice();

    if (AccountModel::getInstance()->PayGold(itemPrice))
    {
        return Inventory::sendItem(aIndex);
    }

    return false;
}


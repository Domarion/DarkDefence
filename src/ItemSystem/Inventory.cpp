#include "Inventory.h"

void Inventory::ConnectModelReceiver(std::function<void(ItemModel)> method)
{
    SendHandler = method;
}

const ItemModel* Inventory::getItemByName(const std::string& aItemName) const
{
    for(const auto& item : items)
    {
        if (item.getCaption() == aItemName)
            return &item;
    }

    return nullptr;
}

void Inventory::clearControllerReceivers()
{
    ReceiveHandler = nullptr;
}

bool Inventory::sendItem(size_t aItemIndex) // TODO refactor. Strange Logic.
{
    if (aItemIndex >= items.size())
    {
        return false;
    }

    if (SendHandler != nullptr && !items[aItemIndex].getCaption().empty())
	{
        SendHandler(items[aItemIndex]);

        if (items.size() != 1 && aItemIndex != items.size() - 1)
        {

            for(size_t i = aItemIndex; i < items.size() - 1; ++i)
            {
                items[i] = items[i + 1];
            }
        }

        items.pop_back();

		return true;
	}
    return false;
}

int Inventory::getItemIndexByName(const std::string& aItemName) const
{
    for(size_t i = 0; i < items.size(); ++i)
    {
        if (items[i].getCaption() == aItemName)
            return i;
    }
    return -1;
}

void Inventory::sendItemWithoutPriceCheck(const std::string& aItemName)
{
    size_t index = getItemIndexByName(aItemName);
    Inventory::sendItem(index);
}

void Inventory::receiveItem(ItemModel aItem)
{
    if (!aItem.getCaption().empty())
    {
        items.push_back(aItem);
        if (ReceiveHandler != nullptr)
        {
            ReceiveHandler(aItem.getCaption(), static_cast<int>(aItem.getItemType()));
        }
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
    ReceiveHandler = handler;
}

vector<std::string> Inventory::getItemNames() const
{
    vector<std::string> itemNames;
    itemNames.reserve((items.size()));

    for(const auto& item : items)
    {
        if (!item.getCaption().empty())
        {
            itemNames.emplace_back(item.getCaption());
        }
    }

    return itemNames;
}

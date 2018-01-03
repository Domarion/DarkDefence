#include "ItemModel.h"

ItemModel::ItemModel(
    const std::string& aCaption, const std::string& aDescription, Enums::ItemTypes aItemType, int aPrice)
    : caption(aCaption)
    , description(aDescription)
    , itemType(aItemType)
    , price(aPrice)
{
}

const std::string& ItemModel::getDescription() const
{
    return description;
}

void ItemModel::setDescription(const std::string& aDescription)
{
    description = aDescription;
}

Enums::ItemTypes ItemModel::getItemType() const
{
    return itemType;
}

void ItemModel::setItemType(Enums::ItemTypes aItemType)
{
    itemType = aItemType;
}

int ItemModel::getPrice() const
{
    return price;
}

void ItemModel::setPrice(int aPrice)
{
    price = aPrice;
}

void ItemModel::clean()
{
    itemType = Enums::ItemTypes::DEFAULT;
    safeClean();
}

const std::string& ItemModel::getCaption() const
{
    return caption;
}

void ItemModel::setCaption(const std::string& aCaption)
{
    caption = aCaption;
}

void ItemModel::safeClean()
{
    caption.clear();
    description.clear();
    price = 0;
}

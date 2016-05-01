/*
 * ItemModel.cpp
 *
 *  Created on: 15 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "ItemModel.h"

ItemModel::ItemModel()
{
	// TODO Auto-generated constructor stub

}

ItemModel::~ItemModel()
{
	// TODO Auto-generated destructor stub
}

const std::string& ItemModel::getDescription() const
{
	return description;
}

void ItemModel::setDescription(const std::string& description)
{
	this->description = description;
}

Enums::ItemTypes ItemModel::getItemType() const
{
	return itemType;
}

void ItemModel::setItemType(Enums::ItemTypes itemType)
{
	this->itemType = itemType;
}

int ItemModel::getPrice() const
{
	return price;
}

void ItemModel::setPrice(int price)
{
	this->price = price;
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

void ItemModel::setCaption(const std::string& caption)
{
	this->caption = caption;
}

void ItemModel::safeClean()
{
	caption.clear();
	description.clear();
	price = 0;
}

/*
 * ItemModel.h
 *
 *  Created on: 15 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once

#include <cereal/access.hpp>
#include <cereal/types/string.hpp>
#include "../Enums.h"

class ItemModel
{
    friend class cereal::access;
    template <typename Archive>
    void serialize(Archive &ar)
	{
        ar(CEREAL_NVP(caption), CEREAL_NVP(description), CEREAL_NVP(itemType), CEREAL_NVP(price));
	}
public:
	ItemModel();
    ItemModel(std::string aCaption, std::string aDescription, Enums::ItemTypes aItemType, int aPrice);
	~ItemModel();
	const std::string& getDescription() const;
	void setDescription(const std::string& description);
	Enums::ItemTypes getItemType() const;
	void setItemType(Enums::ItemTypes itemType);
	int getPrice() const;
	void setPrice(int price);
	void clean();
	void safeClean();
	const std::string& getCaption() const;
	void setCaption(const std::string& caption);

private:
	std::string caption;
	std::string description;
	Enums::ItemTypes itemType;
	int price;

};


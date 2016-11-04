/*
 * ItemModel.h
 *
 *  Created on: 15 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once

#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/version.hpp>
#include <string>
#include "../Enums.h"

class ItemModel
{
	friend class boost::serialization::access;
		template <typename Archive>
          void serialize(Archive &ar, const unsigned int /*version*/)
	{
		ar & BOOST_SERIALIZATION_NVP(caption);
		ar & BOOST_SERIALIZATION_NVP(description);
		ar & BOOST_SERIALIZATION_NVP(itemType);
		ar & BOOST_SERIALIZATION_NVP(price);
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


/*
 * ShopInventory.h
 *
 *  Created on: 17 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once

#include "Inventory.h"
#include <boost/serialization/base_object.hpp>

class ShopInventory: public Inventory
{
	friend class boost::serialization::access;
		template <typename Archive>
			void serialize(Archive& ar, const unsigned int version)
			{
				ar & boost::serialization::make_nvp("Inventory", (boost::serialization::base_object<Inventory>(*this)));
				ar & BOOST_SERIALIZATION_NVP(itemPrices);
			}
public:
	ShopInventory();
	virtual ~ShopInventory();
	virtual bool sendItem(int index) override;
	virtual void addItem(ItemModel item) override;
	void addItemWithPrice(ItemModel item, int price);

private:
	vector<int> itemPrices;
};


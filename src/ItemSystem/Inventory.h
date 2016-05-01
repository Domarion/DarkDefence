/*
 * Inventory.h
 *
 *  Created on: 17 апр. 2016 г.
 *      Author: kostya_hm
 */
#pragma once
#include "ItemModel.h"
#include <boost/serialization/vector.hpp>
#include <boost/serialization/export.hpp>
#include <vector>
using std::vector;
#include <functional>


class Inventory
{
	friend class boost::serialization::access;
	template <typename Archive>
		 void serialize(Archive &ar, const unsigned int version)
		{
			ar & BOOST_SERIALIZATION_NVP(items);
		}
public:
	Inventory();
	virtual ~Inventory();
	virtual bool sendItem(int index);
	virtual void receiveItem(ItemModel item);
	virtual void addItem(ItemModel item);
	void ConnectMethod(std::function<void(ItemModel)> method);
	int getItemCount() const;
	const ItemModel*const getItemFromIndex(int index);
protected:
	vector<ItemModel> items;
	std::function<void(ItemModel)> connectedMethod;




};


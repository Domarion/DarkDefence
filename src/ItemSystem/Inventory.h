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
#include <string>
using std::string;

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

	int getItemCount() const;
    const ItemModel* getItemFromIndex(int index);
    virtual void ConnectReceiver( std::function<void(string, int)> handler);
    virtual void ConnectMethod( std::function<void(ItemModel)> handler);
protected:
	vector<ItemModel> items;
    std::function<void(string, int)> connectedMethod;
    std::function<void(ItemModel)> connectedMethod0;



};


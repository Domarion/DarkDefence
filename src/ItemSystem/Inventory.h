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
            ar & boost::serialization::make_nvp("ArtifactList", items);
		}
public:
	Inventory();
	virtual ~Inventory();
    virtual bool sendItem(size_t index);
    int getItemIndexByName(string name);
	virtual void receiveItem(ItemModel item);
	virtual void addItem(ItemModel item);

	int getItemCount() const;
    const ItemModel* getItemFromIndex(size_t index);
    virtual void ConnectReceiver( std::function<void(string, size_t)> handler);
    virtual void ConnectMethod( std::function<void(ItemModel)> handler);
    virtual ItemModel* getItemByName(string name);

    vector<string> getItemNames();
protected:
	vector<ItemModel> items;
    std::function<void(string, size_t)> connectedMethod;
    std::function<void(ItemModel)> connectedMethod0;



};


/*
 * Inventory.h
 *
 *  Created on: 17 апр. 2016 г.
 *      Author: kostya_hm
 */
#pragma once
#include "ItemModel.h"
#include <cereal/access.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>

#include <functional>
#include <string>
using std::string;
using std::vector;
class Inventory
{
    friend class cereal::access;
	template <typename Archive>
         void serialize(Archive &ar)
		{
            ar(cereal::make_nvp("ArtifactList", items));
		}
public:
	Inventory();
	virtual ~Inventory();
    virtual bool sendItem(size_t index);
    int getItemIndexByName(string name);
    virtual void sendItemWithoutPriceCheck(string name);
	virtual void receiveItem(ItemModel item);
	virtual void addItem(ItemModel item);

	int getItemCount() const;
    const ItemModel* getItemFromIndex(size_t index);
    virtual void ConnectControllerReceiver( std::function<void(string, size_t)> handler);
    virtual void ConnectModelReceiver( std::function<void(ItemModel)> handler);
    virtual ItemModel* getItemByName(string name);
    virtual void clearControllerReceivers();
    vector<string> getItemNames();
protected:
	vector<ItemModel> items;
    std::function<void(string, size_t)> connectedMethod;
    std::function<void(ItemModel)> connectedMethod0;



};

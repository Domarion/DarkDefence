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

    virtual ~Inventory() = default;

    virtual bool sendItem(size_t aItemIndex);
    int getItemIndexByName(const std::string& aItemName) const;
    virtual void sendItemWithoutPriceCheck(const std::string& aItemName);
	virtual void receiveItem(ItemModel item);
    virtual void addItem(const ItemModel& aItem);

	int getItemCount() const;
    const ItemModel* getItemFromIndex(size_t aItemIndex) const;
    virtual void ConnectControllerReceiver( std::function<void(std::string, size_t)> handler);
    virtual void ConnectModelReceiver( std::function<void(ItemModel)> handler);
    virtual const ItemModel* getItemByName(const std::string& aItemName) const;
    virtual void clearControllerReceivers();
    vector<std::string> getItemNames() const;

protected:

	vector<ItemModel> items;

    std::function<void(std::string, size_t)> connectedMethod;
    std::function<void(ItemModel)> connectedMethod0;
};

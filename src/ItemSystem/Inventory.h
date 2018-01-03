#pragma once

#include <functional>

#include "ItemModel.h"
#include <cereal/access.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>

using std::vector;

class Inventory
{
    friend class cereal::access;
	template <typename Archive>
    void serialize(Archive& ar)
    {
        ar(cereal::make_nvp("ArtifactList", items));
    }

public:

    virtual ~Inventory() = default;

    virtual void addItem(const ItemModel& aItem);

    virtual bool sendItem(size_t aItemIndex);
    virtual void sendItemWithoutPriceCheck(const std::string& aItemName);
    virtual void receiveItem(ItemModel aItem);

	int getItemCount() const;
    int getItemIndexByName(const std::string& aItemName) const;
    const ItemModel* getItemFromIndex(size_t aItemIndex) const;
    virtual const ItemModel* getItemByName(const std::string& aItemName) const;
    vector<std::string> getItemNames() const;

    virtual void ConnectControllerReceiver( std::function<void(std::string, size_t)> handler);
    virtual void ConnectModelReceiver( std::function<void(ItemModel)> handler);
    virtual void clearControllerReceivers();
protected:

	vector<ItemModel> items;

    std::function<void(std::string, size_t)> ReceiveHandler;
    std::function<void(ItemModel)> SendHandler;
};

/*
 * ShopInventory.h
 *
 *  Created on: 17 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once

#include "Inventory.h"
//#include <cereal/types/base_class.hpp>
class ShopInventory: public Inventory
{
//    friend class cereal::access;
//    template<typename Archive>
//    void serialize(Archive &ar)
//    {
//       ar(cereal::base_class<Inventory>(this));
//    }

public:
	ShopInventory();
	virtual ~ShopInventory();
    virtual bool sendItem(size_t index) override;
};

//CEREAL_REGISTER_TYPE(ShopInventory)
//CEREAL_REGISTER_POLYMORPHIC_RELATION(Inventory, ShopInventory)

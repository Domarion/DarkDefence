/*
 * ShopController.h
 *
 *  Created on: 20 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include "ShopInventory.h"
#include "../GraphicsSystem/newSystem/ConcreteUIViews/UIScrollList.h"
#include <memory>
class ShopController
{
public:
    ShopController();
    virtual ~ShopController() = default;
    void setView(std::shared_ptr<UIScrollList> &newView);
	void setModel(ShopInventory* newModel);
    ShopInventory*  getModel() const;
    void initView(std::shared_ptr<RenderingSystem> &aRenderer);
    bool sendItemToModel(int index);

private:
	ShopInventory* model;
    std::shared_ptr<UIScrollList> view;
};

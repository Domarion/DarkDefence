#pragma once

#include "ShopInventory.h"
#include "../GraphicsSystem/newSystem/ConcreteUIViews/UIScrollList.h"

class ShopController
{
public:
    ShopController() = default;
    virtual ~ShopController() = default;
    void setView(std::shared_ptr<UIScrollList>&& newView);
    void setModel(std::shared_ptr<ShopInventory> newModel);
    std::shared_ptr<ShopInventory>  getModel() const;
    void initView(std::shared_ptr<RenderingSystem> &aRenderer);
    bool sendItemToModel(int index);
    std::shared_ptr<UIScrollList> getView() const;

private:
    std::shared_ptr<ShopInventory> model;
    std::shared_ptr<UIScrollList> view;
};

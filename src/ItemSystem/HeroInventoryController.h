/*
 * HeroInventoryController.h
 *
 *  Created on: 28 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include "HeroInventory.h"
#include "../GraphicsSystem/newSystem/ConcreteUIViews/UISlotContainer.h"
class HeroInventoryController
{
public:
    HeroInventoryController();
	virtual ~HeroInventoryController();
    void setView(std::shared_ptr<UISlotContainer> newView);
    std::shared_ptr<UISlotContainer> getView() const;
    void setModel(std::shared_ptr<HeroInventory> newModel);
    std::shared_ptr<HeroInventory> getModel() const;
    void initLocalPositions(Size aRectSize);
    void initView(std::shared_ptr<RenderingSystem> &aRenderer);
    void receiveItemFromModel(string caption, size_t itemType);
private:
    std::shared_ptr<HeroInventory> model;
    std::shared_ptr<UISlotContainer> view;
    std::vector<Position> slotsPositions;
};



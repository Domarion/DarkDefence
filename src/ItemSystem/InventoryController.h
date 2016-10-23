/*
 * InventoryController.h
 *
 *  Created on: 24 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once

#include "Inventory.h"
#include "../GraphicsSystem/newSystem/ConcreteUIViews/UIScrollList.h"
//#include "../GraphicsSystem/UI/ScrollList.h"
#include <memory>
#include "../GraphicsSystem/newSystem/IComposite.h"
#include "../GraphicsSystem/newSystem/Font.h"

class InventoryController
{
public:
    explicit InventoryController(std::shared_ptr<RenderingSystem> &aRenderer);
	virtual ~InventoryController();
    void setView(std::shared_ptr<UIScrollList> &newView);
//    ScrollList* getView() const;
	void setModel(Inventory* newModel);
    Inventory* getModel() const;
    void initView();
    void receiveItemFromModel(string caption, size_t itemType);
    bool sendItemToModel(int index);
private:
	Inventory* model;
    std::shared_ptr<UIScrollList> view;
    std::shared_ptr<RenderingSystem> renderer;

    Font arial;
    SDL_Color color;
    vector<std::shared_ptr<IComposite> > buttons;
};


/*
 * InventoryController.cpp
 *
 *  Created on: 24 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "InventoryController.h"
#include "../GraphicsSystem/UI/TextButton.h"

InventoryController::InventoryController()
: model(nullptr), view(nullptr)
{
	// TODO Auto-generated constructor stub

}

InventoryController::~InventoryController()
{
	// TODO Auto-generated destructor stub
}

void InventoryController::setView(ScrollList* newView)
{
	view = newView;
}

ScrollList* const InventoryController::getView() const
{
	return view;
}

void InventoryController::setModel(Inventory* newModel)
{
	model = newModel;
}

Inventory* const InventoryController::getModel() const
{
	return model;
}

void InventoryController::initView()
{
	int count = model->getItemCount();
	if (count == 0)
		return;
	std::cout << "ItemCount = " << count << std::endl;
	for(int i = 0; i != count; ++i)
	{
		TextButton* btn = new TextButton();
		btn->setRenderer(view->getRenderer());

		std::cout << ( "/home/kostya_hm/workspace/DarkDefenceCppPort/GameData/textures/items/" + model->getItemFromIndex(i)->getCaption()  + ".png") << std::endl;

		btn->loadTextureFromFile("/home/kostya_hm/workspace/DarkDefenceCppPort/GameData/textures/items/" + model->getItemFromIndex(i)->getCaption() + ".png");

		if (btn->getTexture() == nullptr)
			std::cout << "index = " << i << " texture is nullptr" << std::endl;

		view->addItem(btn);
	}
	view->calculateVisibleItemsPositions();
}

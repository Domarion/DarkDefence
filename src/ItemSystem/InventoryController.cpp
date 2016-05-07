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


		std::cout << ( "/home/kostya_hm/workspace/DarkDefenceCppPort/GameData/textures/items/" + model->getItemFromIndex(i)->getCaption()  + ".png") << std::endl;
        btn->setTexture( Renderer::getInstance()->loadTextureFromFile("/home/kostya_hm/workspace/DarkDefenceCppPort/GameData/textures/items/" +
                                                                      model->getItemFromIndex(i)->getCaption() + ".png") );

		if (btn->getTexture() == nullptr)
			std::cout << "index = " << i << " texture is nullptr" << std::endl;

		view->addItem(btn);
	}
    view->ConnectMethod(std::bind( &Inventory::sendItem, model, std::placeholders::_1) );
    model->ConnectReceiver(std::bind( &InventoryController::receiveItemFromModel, this, std::placeholders::_1, std::placeholders::_2) );
    view->calculateVisibleItemsPositions();
}

void InventoryController::receiveItemFromModel(string caption, int itemType)
{

    if (caption.empty())
        return;

    TextButton* btn = new TextButton();


    std::cout << ( "/home/kostya_hm/workspace/DarkDefenceCppPort/GameData/textures/items/" + caption  + ".png") << std::endl;
    btn->setTexture( Renderer::getInstance()->loadTextureFromFile("/home/kostya_hm/workspace/DarkDefenceCppPort/GameData/textures/items/" +
                                                                  caption + ".png") );

    if (btn->getTexture() == nullptr)
        std::cout  << " texture is nullptr" << std::endl;

    view->addItem(btn);
    view->calculateVisibleItemsPositions();

}

/*
 * ShopController.cpp
 *
 *  Created on: 20 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "ShopController.h"
#include "../GraphicsSystem/UI/TextButton.h"

ShopController::ShopController()
: model(nullptr), view(nullptr)
{
	// TODO Auto-generated constructor stub

}

ShopController::~ShopController()
{
	// TODO Auto-generated destructor stub
}

void ShopController::setView(ScrollList* newView)
{
	view = newView;
}

ScrollList* const ShopController::getView() const
{
	return view;
}

void ShopController::setModel(ShopInventory* newModel)
{
	model = newModel;
}

ShopInventory* const ShopController::getModel() const
{
	return model;
}

void ShopController::initView()
{
	int count = model->getItemCount();
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
	view->calculateVisibleItemsPositions();
	view->ConnectMethod(std::bind( &ShopInventory::sendItem, model, std::placeholders::_1) );
}

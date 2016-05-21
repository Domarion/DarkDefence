/*
 * ShopController.cpp
 *
 *  Created on: 20 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "ShopController.h"
//#include "../GraphicsSystem/UI/TextButton.h"
#include "../GraphicsSystem/ShopItemUI.h"

ShopController::ShopController()
: model(nullptr), view(nullptr), arial(nullptr)
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

     arial = Renderer::getInstance()->loadFontFromFile("/home/kostya_hm/Projects/DarkDefence/Fonts/arial.ttf", 20);
    color = {0, 0, 0};


	int count = model->getItemCount();
	std::cout << "ItemCount = " << count << std::endl;
	for(int i = 0; i != count; ++i)
	{
        //TextButton* btn = new TextButton();
        ShopItemUI *btn =  new ShopItemUI();

        string ipath = "/home/kostya_hm/workspace/DarkDefenceCppPort/GameData/textures/items/" +
                model->getItemFromIndex(i)->getCaption() + ".png";
        string iprice = std::to_string(model->getItemFromIndex(i)->getPrice());
        btn->init(arial,color,ipath,model->getItemFromIndex(i)->getCaption(), model->getItemFromIndex(i)->getDescription(), iprice );


        view->setItemWidth(btn->getRect().w);
        view->setItemHeight(btn->getRect().h);
        //std::cout << ( "/home/kostya_hm/workspace/DarkDefenceCppPort/GameData/textures/items/" + model->getItemFromIndex(i)->getCaption()  + ".png") << std::endl;

        //btn->setTexture( Renderer::getInstance()->loadTextureFromFile("/home/kostya_hm/workspace/DarkDefenceCppPort/GameData/textures/items/" +
                                                                      //model->getItemFromIndex(i)->getCaption() + ".png") );

        //if (btn->getTexture() == nullptr)
            //std::cout << "index = " << i << " texture is nullptr" << std::endl;

		view->addItem(btn);
	}
	view->calculateVisibleItemsPositions();
	view->ConnectMethod(std::bind( &ShopInventory::sendItem, model, std::placeholders::_1) );
}

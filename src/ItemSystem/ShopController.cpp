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
: model(nullptr), view(nullptr), arial()
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

ScrollList*  ShopController::getView() const
{
	return view;
}

void ShopController::setModel(ShopInventory* newModel)
{
	model = newModel;
}

ShopInventory*  ShopController::getModel() const
{
	return model;
}

void ShopController::initView()
{

    arial.loadFromFile("Fonts/arial.ttf", 20);



	int count = model->getItemCount();
	std::cout << "ItemCount = " << count << std::endl;
	for(int i = 0; i != count; ++i)
	{
        //TextButton* btn = new TextButton();
        ShopItemUI *btn =  new ShopItemUI();

        string ipath = "GameData/textures/items/" +
                model->getItemFromIndex(i)->getCaption() + ".png";
        string iprice = std::to_string(model->getItemFromIndex(i)->getPrice());
        btn->init(arial,ipath,model->getItemFromIndex(i)->getCaption(), model->getItemFromIndex(i)->getDescription(), iprice );


        view->setItemWidth(btn->getRect().w);
        view->setItemHeight(btn->getRect().h);
        //std::cout << ( "GameData/textures/items/" + model->getItemFromIndex(i)->getCaption()  + ".png") << std::endl;



        //if (btn->getTexture() == nullptr)
            //std::cout << "index = " << i << " texture is nullptr" << std::endl;

		view->addItem(btn);
	}
	view->calculateVisibleItemsPositions();
	view->ConnectMethod(std::bind( &ShopInventory::sendItem, model, std::placeholders::_1) );
}

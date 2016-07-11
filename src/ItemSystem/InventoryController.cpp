/*
 * InventoryController.cpp
 *
 *  Created on: 24 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "InventoryController.h"
//#include "../GraphicsSystem/UI/TextButton.h"
#include "../GraphicsSystem/ShopItemUI.h"

InventoryController::InventoryController()
: model(nullptr), view(nullptr), arial(new CFont())
{
	// TODO Auto-generated constructor stub

}

InventoryController::~InventoryController()
{

   // for(size_t i = 0; i < buttons.size(); ++i)
     //   delete buttons[i];
	// TODO Auto-generated destructor stub
}

void InventoryController::setView(ScrollList* newView)
{
	view = newView;
}

ScrollList*  InventoryController::getView() const
{
	return view;
}

void InventoryController::setModel(Inventory* newModel)
{
	model = newModel;
}

Inventory*  InventoryController::getModel() const
{
	return model;
}

void InventoryController::initView()
{
    arial.get()->loadFromFile("Fonts/arial.ttf", 20);


	int count = model->getItemCount();
	if (count == 0)
		return;
	std::cout << "ItemCount = " << count << std::endl;
	for(int i = 0; i != count; ++i)
	{



        ShopItemUI *btn =  new ShopItemUI();

       // buttons.push_back(btn);
        string ipath = "GameData/textures/items/" +
                model->getItemFromIndex(i)->getCaption() + ".png";

        btn->init(arial,ipath,model->getItemFromIndex(i)->getCaption(), model->getItemFromIndex(i)->getDescription());


        view->setItemWidth(btn->getRect().w);
        view->setItemHeight(btn->getRect().h);
        //TextButton* btn = new TextButton();


        //std::cout << ( "GameData/textures/items/" + model->getItemFromIndex(i)->getCaption()  + ".png") << std::endl;

        //if (btn->getTexture() == nullptr)
            //std::cout << "index = " << i << " texture is nullptr" << std::endl;

		view->addItem(btn);
	}
    view->ConnectMethod(std::bind( &Inventory::sendItem, model, std::placeholders::_1) );
    model->ConnectReceiver(std::bind( &InventoryController::receiveItemFromModel, this, std::placeholders::_1, std::placeholders::_2) );
    view->calculateVisibleItemsPositions();
}

void InventoryController::receiveItemFromModel(string caption, size_t itemType)
{

    if (caption.empty())
        return;



    ShopItemUI *btn =  new ShopItemUI();

    string ipath = "GameData/textures/items/" +
            caption + ".png";



    btn->init(arial, ipath, caption, "descr stub");



    /*TextButton* btn = new TextButton();


    std::cout << ( "GameData/textures/items/" + caption  + ".png") << std::endl;


    if (btn->getTexture() == nullptr)
        std::cout  << " texture is nullptr" << std::endl;*/

    view->addItem(btn);
    view->calculateVisibleItemsPositions();

}

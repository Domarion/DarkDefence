/*
 * ShopController.cpp
 *
 *  Created on: 20 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "ShopController.h"
#include "../GraphicsSystem/ShopItemUI.h"
#include "../Grouping/FontManager.h"

ShopController::ShopController()
: model(nullptr), view(nullptr)
{
	// TODO Auto-generated constructor stub

}

ShopController::~ShopController()
{
    view = nullptr;
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

	int count = model->getItemCount();
	std::cout << "ItemCount = " << count << std::endl;
	for(int i = 0; i != count; ++i)
	{
        ShopItemUI* btn = new ShopItemUI();

        string ipath = "GameData/textures/items/" +
                model->getItemFromIndex(i)->getCaption() + ".png";
        string iprice = std::to_string(model->getItemFromIndex(i)->getPrice());
        btn->init(FontManager::getInstance()->getFontByKind("TextFont"),ipath,model->getItemFromIndex(i)->getCaption(), model->getItemFromIndex(i)->getDescription(), iprice );


        view->setItemWidth(btn->getRect().w);
        view->setItemHeight(btn->getRect().h);




        view->addItem(btn);
	}
	view->calculateVisibleItemsPositions();
    view->ConnectMethod(std::bind( &ShopController::sendItemToModel, this, std::placeholders::_1) );
}

bool ShopController::sendItemToModel(int index)
{
    if (model->sendItem(index))
    {
        view->removeItem(index);
        return true;
    }
    return false;
}

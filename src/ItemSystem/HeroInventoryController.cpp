/*
 * HeroInventoryController.cpp
 *
 *  Created on: 28 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "HeroInventoryController.h"
#include "../GraphicsSystem/UI/TextButton.h"
HeroInventoryController::HeroInventoryController()
:model(nullptr), view(nullptr)
{
	// TODO Auto-generated constructor stub

}

HeroInventoryController::~HeroInventoryController()
{
	// TODO Auto-generated destructor stub
}

void HeroInventoryController::setView(SlotContainer* newView)
{
	view = newView;
}

SlotContainer*  HeroInventoryController::getView() const
{
	return view;
}

void HeroInventoryController::setModel(HeroInventory* newModel)
{
	model = newModel;
}

HeroInventory*  HeroInventoryController::getModel() const
{
	return model;
}

void HeroInventoryController::initView()
{
	int count = model->getItemCount();
	if (count == 0)
		return;
	std::cout << "ItemCount = " << count << std::endl;
	for(int i = 0; i != count; ++i)
	{
		TextButton* btn = new TextButton();

        if (model->getItemFromIndex(i)->getDescription() == "none")
        {
            btn->setTexture( Renderer::getInstance()->loadTextureFromFile("/home/kostya_hm/Projects/DarkDefence/GameData/textures/EmptySlot.png" ) );
        }
        else
        {
            std::cout << ( "/home/kostya_hm/workspace/DarkDefenceCppPort/GameData/textures/items/" + model->getItemFromIndex(i)->getCaption()  + ".png") << std::endl;
            btn->setTexture( Renderer::getInstance()->loadTextureFromFile("/home/kostya_hm/workspace/DarkDefenceCppPort/GameData/textures/items/"
                                                                            + model->getItemFromIndex(i)->getCaption() + ".png") );
        }
		if (btn->getTexture() == nullptr)
            std::cout << "index = " << i << " herotexture is nullptr" << std::endl;

		view->addItem(btn, i);
	}
	int itemWidth = 50;
	int itemHeight = 50;

    int centerX = view->getRect().x + static_cast<int>(view->getRect().w * 0.5) +itemWidth;
    int y = 0;
    view->setItemRect(0, centerX, y, itemWidth, itemHeight);
    y += itemHeight;

    view->setItemRect(1, centerX, y, itemWidth, itemHeight);
     y += itemHeight;

    view->setItemRect(2, centerX - itemWidth, y, itemWidth, itemHeight);
    view->setItemRect(3, centerX, y, itemWidth, itemHeight);
    view->setItemRect(4, centerX + itemWidth, y, itemWidth, itemHeight);

    view->setItemRect(5, centerX - 2*itemWidth, y - itemHeight, itemWidth, itemHeight);

    y += itemHeight;

    view->setItemRect(6, centerX, y, itemWidth, itemHeight);
   // y += itemHeight;
    view->setItemRect(7, centerX + 2*itemWidth, y, itemWidth, itemHeight);
    view->setItemRect(8, centerX + 3*itemWidth, y, itemWidth, itemHeight);
    view->ConnectMethod(std::bind( &HeroInventory::sendItem, model, std::placeholders::_1) );
    model->ConnectReceiver(std::bind( &HeroInventoryController::receiveItemFromModel, this, std::placeholders::_1, std::placeholders::_2) );
}


void HeroInventoryController::receiveItemFromModel(string caption, int itemType)
{

    if (caption.empty())
        return;

    TextButton* btn = new TextButton();


    std::cout << ( "/home/kostya_hm/workspace/DarkDefenceCppPort/GameData/textures/items/" + caption  + ".png") << std::endl;
    btn->setTexture( Renderer::getInstance()->loadTextureFromFile("/home/kostya_hm/workspace/DarkDefenceCppPort/GameData/textures/items/" +
                                                                  caption + ".png") );

    if (btn->getTexture() == nullptr)
        std::cout << " texture is nullptr" << std::endl;

    view->receiveItem(btn, itemType);


}

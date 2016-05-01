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

SlotContainer* const HeroInventoryController::getView() const
{
	return view;
}

void HeroInventoryController::setModel(HeroInventory* newModel)
{
	model = newModel;
}

HeroInventory* const HeroInventoryController::getModel() const
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
		btn->setRenderer(view->getRenderer());

		std::cout << ( "/home/kostya_hm/workspace/DarkDefenceCppPort/GameData/textures/items/" + model->getItemFromIndex(i)->getCaption()  + ".png") << std::endl;

		btn->loadTextureFromFile("/home/kostya_hm/workspace/DarkDefenceCppPort/GameData/textures/items/" + model->getItemFromIndex(i)->getCaption() + ".png");

		if (btn->getTexture() == nullptr)
			std::cout << "index = " << i << " texture is nullptr" << std::endl;

		view->addItem(btn, i);
	}
	int itemWidth = 50;
	int itemHeight = 50;
	SDL_Rect* r0 = new SDL_Rect({0,0, itemWidth, itemHeight});
	view->setItemRect(0, r0);
	SDL_Rect* r1 = new SDL_Rect({0,0, itemWidth, itemHeight});
	view->setItemRect(1, r1);
	SDL_Rect* r2 = new SDL_Rect(
	{ 0, 0, itemWidth, itemHeight });
	view->setItemRect(2, r2);
	SDL_Rect* r3 = new SDL_Rect(
	{ 0, 0, itemWidth, itemHeight });
	view->setItemRect(3, r3);
	SDL_Rect* r4 = new SDL_Rect(
	{ 0, 0, itemWidth, itemHeight });
	view->setItemRect(4, r4);
	SDL_Rect* r5 = new SDL_Rect(
	{ 0, 0, itemWidth, itemHeight });
	view->setItemRect(5, r5);
	SDL_Rect* r6 = new SDL_Rect(
	{ 0, 0, itemWidth, itemHeight });
	view->setItemRect(6, r6);
	SDL_Rect* r7 = new SDL_Rect(
	{ 0, 0, itemWidth, itemHeight });
	view->setItemRect(7, r7);
	SDL_Rect* r8 = new SDL_Rect(
	{ 0, 0, itemWidth, itemHeight });
	view->setItemRect(8, r8);
	SDL_Rect* r9 = new SDL_Rect(
	{ 0, 0, itemWidth, itemHeight });
	view->setItemRect(9, r9);

}

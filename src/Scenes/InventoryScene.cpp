/*
 * InventoryScene.cpp
 *
 *  Created on: 18 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "InventoryScene.h"
#include "../GlobalScripts/GameModel.h"



InventoryScene::InventoryScene(std::shared_ptr<RenderingSystem> &aRenderer)
    :Scene(aRenderer)
    , inventoryController(nullptr)
    , heroController(nullptr)
{
}

InventoryScene::~InventoryScene()
{
    clear();
}

void InventoryScene::init(std::shared_ptr<SceneManager> sceneManagerPtr)
{
    renderer->setRendererDrawColor(255, 255, 255, 255);
    Scene::init(sceneManagerPtr);

    initControlButton();
    initHeroView();
    initInventoryView();
    Scene::addToUIList(MainRect);
}

void InventoryScene::clear()
{
    delete inventoryController;
    delete heroController;
    Scene::clear();
}

void InventoryScene::initControlButton()
{

    Position pos(MainRect->getSize().width - 100, MainRect->getSize().height - 50);

    Scene::addLoadSceneButton("Назад", "ButtonFont", "MainScene",
                pos.x, pos.y, 100, 50);
}

void InventoryScene::initHeroView()
{
    heroController =  new HeroInventoryController();
    heroController->setModel(GameModel::getInstance()->getHeroInventory());
    heroController->initLocalPositions(MainRect->getSize());
    heroController->initView(renderer);
    auto items = heroController->getView()->getItems();
    for(auto& item : items)
    {
        MainRect->addChild(item);
    }

  Scene::addAsInputHandler(heroController->getView().get());

    //Scene::addToUIList(heroFigure);
}

void InventoryScene::initInventoryView()
{
    if (GameModel::getInstance()->getInventory()->getItemCount() > 0)
    {
        const int showItems = 5;
        auto scroll = std::make_shared<UIScrollList>(showItems, renderer);

        inventoryController = new InventoryController(renderer);
        inventoryController->setModel(GameModel::getInstance()->getInventory());
        inventoryController->setView(scroll);
        inventoryController->initView();

        MainRect->addChild(scroll);
    }
}


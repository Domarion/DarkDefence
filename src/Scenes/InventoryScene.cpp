/*
 * InventoryScene.cpp
 *
 *  Created on: 18 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "InventoryScene.h"
#include "../GlobalScripts/GameModel.h"
#include "../GraphicsSystem/newSystem/VerticalLayout.h"

InventoryScene::InventoryScene(
    std::shared_ptr<RenderingSystem>& aRenderer, std::shared_ptr<InputDispatcher> aInputDispatcher)
    : Scene(aRenderer, aInputDispatcher)
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
    Scene::clear();
    heroController.reset();
    inventoryController.reset();
    GameModel::getInstance()->getHeroInventory()->clearControllerReceivers();
    GameModel::getInstance()->getInventory()->clearControllerReceivers();
}

void InventoryScene::initControlButton()
{
    Position pos(MainRect->getSize().width - 100, MainRect->getSize().height - 50);

    Scene::addLoadSceneButton("Назад", "ButtonFont", "MainScene",
                              pos.x, pos.y, 100, 50);
}

void InventoryScene::initHeroView()
{
    heroController =  std::make_unique<HeroInventoryController>();
    auto heroInventory = GameModel::getInstance()->getHeroInventory();
    heroInventory->clearControllerReceivers();

    heroController->setModel(heroInventory);
    heroController->initLocalPositions(MainRect->getSize());
    heroController->initView(renderer);
    auto items = heroController->getView()->getItems();

    for(auto& item : items)
    {
        MainRect->addChild(item);
    }

    Scene::addAsInputHandler(heroController->getView());
}

void InventoryScene::initInventoryView()
{
//   if (GameModel::getInstance()->getInventory()->getItemCount() > 0)
//   {
    const int showItems = 5;
    auto layout = std::make_shared<VerticalLayout>();

    auto scroll = std::make_shared<UIScrollList>(showItems, renderer, layout);

    inventoryController = std::make_unique<InventoryController>(renderer);
    auto inventory = GameModel::getInstance()->getInventory();
    inventory->clearControllerReceivers();
    inventoryController->setModel(inventory);
    inventoryController->setView(scroll);
    inventoryController->initView();

    MainRect->addChild(scroll);
//    }
}


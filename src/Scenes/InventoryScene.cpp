/*
 * InventoryScene.cpp
 *
 *  Created on: 18 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "InventoryScene.h"
#include "../GlobalScripts/GameModel.h"



InventoryScene::InventoryScene()
    :inventoryController(nullptr), heroController(nullptr)
{
}

InventoryScene::~InventoryScene()
{
    clear();
}

void InventoryScene::init( SceneManager* sceneManagerPtr)
{
    Renderer::getInstance()->setRendererDrawColor(255, 255, 255);
    Scene::init(sceneManagerPtr);

    initControlButton();
    initHeroView();
    initInventoryView();
}

void InventoryScene::clear()
{
    delete inventoryController;
    delete heroController;
    Scene::clear();
}

void InventoryScene::initControlButton()
{
    Scene::addLoadSceneButton("Назад", "ButtonFont", "MainScene",
                Renderer::getInstance()->getScreenWidth() - 100, Renderer::getInstance()->getScreenHeight() - 50,
                              100, 50);
}

void InventoryScene::initHeroView()
{
    SlotContainer* heroFigure = new SlotContainer();

    heroFigure->setRect(300,0, 300, 500);
    heroController =  new HeroInventoryController();
    heroController->setModel(GameModel::getInstance()->getHeroInventory());
    heroController->setView(heroFigure);
    heroController->initView();

    Scene::addToUIList(heroFigure);
}

void InventoryScene::initInventoryView()
{
    if (GameModel::getInstance()->getInventory()->getItemCount() > 0)
    {
        const int showItems = 5;
        const int itemWidth = 72;
        const int itemHeight = 72;

        ScrollList* scroll = new ScrollList();
        scroll->initScrollList(showItems, itemWidth, itemHeight);
        scroll->setRect(0, 0, Renderer::getInstance()->getScreenWidth()*0.4, Renderer::getInstance()->getScreenHeight() - 50);
        scroll->loadTexture("GameData/textures/topPanel.png");

        inventoryController = new InventoryController();
        inventoryController->setModel(GameModel::getInstance()->getInventory());


        inventoryController->setView(scroll);
        inventoryController->initView();

        Scene::addToUIList(scroll);
    }
}


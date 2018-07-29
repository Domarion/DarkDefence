#include <cassert>

#include "InventoryScene.h"
#include "../GlobalScripts/GameModel.h"
#include "../GraphicsSystem/newSystem/VerticalLayout.h"
#include "../Logging/Logger.h"
#include "../GraphicsSystem/newSystem/UIElement/UIImage.h"
#include "../GlobalScripts/ResourceManager.h"

InventoryScene::InventoryScene(
    std::shared_ptr<RenderingSystem>& aRenderer, std::shared_ptr<InputDispatcher> aInputDispatcher)
    : Scene(aRenderer, aInputDispatcher)
{
}

void InventoryScene::init()
{
    renderer->setRendererDrawColor(255, 255, 255, 255);
    Scene::init();

    auto backGroundImage = std::make_shared<UIImage>(renderer);
    auto resourceManager = ResourceManager::getInstance();
    assert(resourceManager);
    if (!resourceManager->hasTexture("InventorySceneBackground"))
    {
        LOG_ERROR("Texture for InventorySceneBackground was not found.");
        throw std::runtime_error("Texture for InventorySceneBackground was not found.");
    }

    backGroundImage->setTexture(resourceManager->getTexture("InventorySceneBackground"));
    MainRect->addChild(backGroundImage);
    backGroundImage->setSize(MainRect->getSize());

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
    Scene::addLoadSceneButton("MainScene", Position{0, MainRect->getSize().height - 120}, SceneChange::Prev);
}

void InventoryScene::initHeroView()
{
    heroController =  std::make_unique<HeroInventoryController>();
    auto heroInventory = GameModel::getInstance()->getHeroInventory();
    heroInventory->clearControllerReceivers();

    heroController->setModel(heroInventory);
//    heroController->initLocalPositions(MainRect->getSize());
    heroController->initView(renderer, "GameData/HeroInventoryConfig.json");
    auto items = heroController->getView()->getItems();

    for(auto& item : items)
    {
        MainRect->addChild(item);
    }

    Scene::addAsInputHandler(heroController->getView());
}

void InventoryScene::initInventoryView()
{
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
}


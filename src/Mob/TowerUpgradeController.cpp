#include "TowerUpgradeController.h"
#include "../GlobalScripts/GameModel.h"
#include <iostream>
#include "../Input/InputDispatcher.h"
#include "../GraphicsSystem/newSystem/UIElement/ConcreteComposite.h"
#include "../GraphicsSystem/newSystem/UIElement/UILabel.h"
#include "../GraphicsSystem/newSystem/UIElement/UIImageButton.h"
#include "../GraphicsSystem/newSystem/UIElement/UITextButton.h"
#include "../Scenes/GameScene.h"

TowerUpgradeController::TowerUpgradeController()
    : parentGameScene(nullptr)
    , cachedTower(nullptr)
    , towerMenu(nullptr)
    , fabric(std::make_unique<TowerFabric>())
    , upgradeGroup(nullptr)
{


}

TowerUpgradeController::~TowerUpgradeController()
{
    upgradeGroup.reset();
    fabric.reset();
}

void TowerUpgradeController::init(std::shared_ptr<Scene> parent, std::shared_ptr<RenderingSystem>& aRenderer)
{
    parentGameScene = parent;
    renderer = aRenderer;
}

void TowerUpgradeController::receiveTowerUpgrade(std::shared_ptr<Tower> tower)
{
    if (tower == nullptr || parentGameScene == nullptr)
    {
        return;
    }

    auto gameScene = std::dynamic_pointer_cast<GameScene>(parentGameScene);

    if (gameScene != nullptr && gameScene->getGameSceneStatus() != Enums::GameSceneStatuses::Default)
    {
        return;
    }

    Font arial1Font(FontManager::getInstance()->getFontByKind2("TextFont"));

    cachedTower = tower;

    auto towerName = tower->getName();
    auto currentGrade = GameModel::getInstance()->getRootTower()->recursiveSearch(towerName);

    if (currentGrade == nullptr || currentGrade->hasChildren() == false)
        return;

    Size parentSize = parentGameScene->getMainRect()->getSize();

    upgradeGroup = std::make_shared<ConcreteComposite>(renderer);
    upgradeGroup->setSize(Size(150, 400));
    upgradeGroup->setPosition(Position(parentSize.width/2 - 150, 50));

    currentTowerChildrenNames = currentGrade->getChildrenNames();

    auto currentTowerChildren = currentGrade->getChildren();
    towerMenu = std::make_shared<UIScrollList>(currentTowerChildrenNames.size() + 1, renderer);
    towerMenu->setSize(Size(100, 350));

    const int iconWidth = 48;
    const int iconWidthSmall = 22;

    for(auto& childrenName: currentTowerChildrenNames)
    {
        auto childModel = currentTowerChildren.at(childrenName)->getData();

        auto menuItemGroup = std::make_shared<ConcreteComposite>(renderer);
        menuItemGroup->setSize(Size(100, 100));
        string iconPath = "GameData/textures/Towers/UpgradeIcons/" + childrenName +".jpg";

        auto upgradeIcon = std::make_shared<UIImage>(renderer);
        upgradeIcon->loadTexture(iconPath);
        upgradeIcon->setSize(Size(iconWidth, iconWidth));
        menuItemGroup->addChild(upgradeIcon);

        auto upgradeName = std::make_shared<UILabel>(childrenName, arial1Font, renderer);
        upgradeName->setPosition(menuItemGroup->getNextHorizontalPosition());
        menuItemGroup->addChild(upgradeName);

        auto priceGroup = std::make_shared<ConcreteComposite>(renderer);
        priceGroup->setSize(Size(menuItemGroup->getSize().width, menuItemGroup->getSize().height/2));
        Position priceGroupPos = Position(upgradeName->getLocalPosition().x, menuItemGroup->getNextVerticalPosition().y);
        priceGroup->setPosition(priceGroupPos);

        auto childPrice = childModel->getPrice();

        for(size_t i = 0; i < GlobalConstants::resourceTypeCount; ++i)
        {
            auto resourceIcon = std::make_shared<UIImage>(renderer);
            string resourceName = GameModel::getInstance()->getResourcesModel()->getResourceNameFromIndex(i);
            string RiconPath = "GameData/textures/Resources/" + resourceName + ".png";

            resourceIcon->loadTexture(RiconPath);
            resourceIcon->setSize(Size(iconWidthSmall, iconWidthSmall));
            resourceIcon->setPosition(priceGroup->getNextHorizontalPosition());
            priceGroup->addChild(resourceIcon);

            auto upgradePriceLabel = std::make_shared<UILabel>(std::to_string(childPrice[i]), arial1Font, renderer);
            upgradePriceLabel->setPosition(priceGroup->getNextHorizontalPosition());
            priceGroup->addChild(upgradePriceLabel);
        }

        auto buyButton = std::make_shared<UITextButton>("Купить", arial1Font, renderer);
        buyButton->setPosition(priceGroup->getNextHorizontalPosition());
        buyButton->ConnectMethod(std::bind(&TowerUpgradeController::stub, this, std::placeholders::_1));
        priceGroup->addChild(buyButton);

        menuItemGroup->addChild(priceGroup);
        towerMenu->addChild(menuItemGroup);
    }

    upgradeGroup->addChild(towerMenu);

    std::string closeIconPath = "GameData/textures/Towers/UpgradeIcons/CloseLabel.png";
    auto closeButton = std::make_shared<UIImageButton>(renderer);
    closeButton->loadTexture(closeIconPath);
    closeButton->setSize(Size(50,50));
    closeButton->setPosition(Position(upgradeGroup->getSize().width/2 - 25, upgradeGroup->getNextVerticalPosition().y));
    std::string none {"none"};

    closeButton->ConnectMethod(std::bind(&TowerUpgradeController::closeHandler, this, none));
    upgradeGroup->addChild(closeButton);

    if (parentGameScene != nullptr)
    {
        towerMenu->ConnectMethod(std::bind(&TowerUpgradeController::menuClickHandler, this, std::placeholders::_1));

        parentGameScene->getMainRect()->addChild(upgradeGroup);
    }

    if (gameScene != nullptr)
        gameScene->setGameSceneStatus(Enums::GameSceneStatuses::Menu);
}

void TowerUpgradeController::closeHandler(std::string /*itemIndex*/)
{
    if (parentGameScene == nullptr)
    {
        return;
    }

    parentGameScene->getMainRect()->removeChild(upgradeGroup);
    upgradeGroup.reset();

    auto gameScene = std::dynamic_pointer_cast<GameScene>(parentGameScene);

    if (gameScene != nullptr)
    {
        gameScene->setGameSceneStatus(Enums::GameSceneStatuses::Default);
    }
}

std::shared_ptr<Tower> TowerUpgradeController::ProduceTower(
    const std::string& aTowerName, std::shared_ptr<TileMapManager> aTileMap)
{
    if (!fabric || !parentGameScene)
    {
        return nullptr;
    }

    return fabric->produceTower(aTowerName, parentGameScene->getRenderer(), shared_from_this(), aTileMap);
}

bool TowerUpgradeController::menuClickHandler(size_t itemIndex)
{
    if (parentGameScene == nullptr || cachedTower == nullptr)
    {
        return false;
    }

    auto gameScene = std::dynamic_pointer_cast<GameScene>(parentGameScene);

    if (itemIndex == currentTowerChildrenNames.size())
    {
        if (gameScene != nullptr)
        {
            gameScene->setGameSceneStatus(Enums::GameSceneStatuses::Default);
        }

        return false;
    }

    auto towerName = currentTowerChildrenNames[itemIndex];

    auto rootTower = GameModel::getInstance()->getRootTower();
    if (rootTower == nullptr)
    {
        return false;

    }

    auto searchresult = rootTower->recursiveSearch(towerName);
    if (searchresult == nullptr)
    {
        return false;
    }

    MobModel model(*searchresult->getData());

    if (GameModel::getInstance()->getResourcesModel()->canBuy(model.getPrice()))
    {
        GameModel::getInstance()->getResourcesModel()->removeResources(model.getPrice());

        int x = cachedTower->getSprite()->getPosition().x;
        int y = cachedTower->getSprite()->getPosition().y;
        parentGameScene->destroyObject(cachedTower);

        parentGameScene->getMainRect()->removeChild(upgradeGroup);
        upgradeGroup.reset();

        cachedTower = ProduceTower(towerName, cachedTower->getTileMapManager());

        if (cachedTower == nullptr)
        {
            return false;
        }

        parentGameScene->spawnObject(x, y, cachedTower);

        cachedTower.reset();

        if (gameScene != nullptr)
        {
            gameScene->setGameSceneStatus(Enums::GameSceneStatuses::Default);
        }

        return true;
    }

    return false;
}

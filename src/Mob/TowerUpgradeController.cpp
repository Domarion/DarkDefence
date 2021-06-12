#include "TowerUpgradeController.h"
#include "../GlobalScripts/GameModel.h"
#include "../Input/InputDispatcher.h"
#include "../GraphicsSystem/newSystem/UIElement/ConcreteComposite.h"
#include "../GraphicsSystem/newSystem/UIElement/UILabel.h"
#include "../GraphicsSystem/newSystem/UIElement/UIImageButton.h"
#include "../GraphicsSystem/newSystem/UIElement/UITextButton.h"
#include "../GraphicsSystem/newSystem/VerticalLayout.h"
#include "../GraphicsSystem/newSystem/StubLayout.h"

#include "../GraphicsSystem/newSystem/ConcreteUIViews/AnimationSceneSprite.h"
#include "../GlobalScripts/ResourceManager.h"

#include "../Scenes/GameScene.h"
#include "../Mob/Tower.h"

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

    const auto& arial1Font = FontManager::getInstance()->getFontByKind("ItemFont");

    cachedTower = tower;

    auto towerName = tower->getName();
    auto currentGrade = GameModel::getInstance()->getRootTower()->recursiveSearch(towerName);

    if (currentGrade == nullptr || currentGrade->hasChildren() == false)
        return;

    Size parentSize = parentGameScene->getMainRect()->getSize();
    auto layout = std::make_shared<StubLayout>();
    upgradeGroup = std::make_shared<ConcreteComposite>(renderer, layout);
    upgradeGroup->setSize(Size(150, 500));
    upgradeGroup->setPosition(Position(parentSize.width/2 - 150, 50));

    currentTowerChildrenNames = currentGrade->getChildrenNames();

    auto verticalLayout = std::make_shared<VerticalLayout>();
    auto currentTowerChildren = currentGrade->getChildren();
    towerMenu = std::make_shared<UIScrollList>(currentTowerChildrenNames.size() + 1, renderer, verticalLayout);
    towerMenu->setSize(Size(150, 450));

    const int iconWidth = 64;
    const int iconWidthSmall = 48;

    for(auto& childrenName: currentTowerChildrenNames)
    {
        auto childModel = currentTowerChildren.at(childrenName)->getData();

        auto menuItemGroup = std::make_shared<ConcreteComposite>(renderer, layout);
        menuItemGroup->setSize(Size(150, 150));
        string iconPath = "GameData/textures/Towers/UpgradeIcons/" + childrenName +".jpg";

        auto upgradeIcon = std::make_shared<UIImage>(renderer);
        upgradeIcon->loadTexture(iconPath);
        upgradeIcon->setSize(Size(iconWidth, iconWidth));
        menuItemGroup->addChild(upgradeIcon);

        auto upgradeName = std::make_shared<UILabel>(childrenName, arial1Font, renderer);
        upgradeName->setPosition(menuItemGroup->getNextHorizontalPosition());
        menuItemGroup->addChild(upgradeName);

        auto priceGroup = std::make_shared<ConcreteComposite>(renderer, layout);
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

        auto buyButton = std::make_shared<UIImageButton>(renderer);
        buyButton->setPosition(priceGroup->getNextHorizontalPosition());
        buyButton->setTexture(ResourceManager::getInstance()->getTexture("BuyButton"));
        buyButton->setSize(Size(iconWidth, iconWidth));
        buyButton->ConnectMethod(std::bind(&TowerUpgradeController::stub, this, std::placeholders::_1));
        priceGroup->addChild(buyButton);

        menuItemGroup->addChild(priceGroup);
        towerMenu->addChild(menuItemGroup);
    }

    upgradeGroup->addChild(towerMenu);

    std::string closeIconPath = "GameData/textures/Towers/UpgradeIcons/CloseLabel.png";
    auto closeButton = std::make_shared<UIImageButton>(renderer);
    closeButton->loadTexture(closeIconPath);
    closeButton->setSize(Size(iconWidth,iconWidth));
    closeButton->setPosition(Position(
        upgradeGroup->getSize().width/2 - 25,
        upgradeGroup->getNextVerticalPosition().y + iconWidth));
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
    const std::string& aTowerName, const TileMapManager& aTileMap, size_t aDrawPriority)
{
    if (!parentGameScene)
    {
        return nullptr;
    }

    auto model = GameModel::getInstance()->getTowerByName(aTowerName);

    if (model == nullptr)
    {
        return nullptr;
    }

    auto tower = std::make_shared<Tower>(std::move(model), aTileMap);
    auto someSprite = std::make_shared<AnimationSceneSprite>(parentGameScene->getRenderer());

    someSprite->setTexture(ResourceManager::getInstance()->getTexture(aTowerName));
    someSprite->setDrawPriority(aDrawPriority);

    tower->setSprite(someSprite);

    tower->connectMethod(
        std::bind(&TowerUpgradeController::receiveTowerUpgrade, this, std::placeholders::_1));

    tower->init(0, 0);


    return tower;
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

    const auto& towerName = currentTowerChildrenNames[itemIndex];

    auto& rootTower = GameModel::getInstance()->getRootTower();
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

        auto oldcached = cachedTower;
        parentGameScene->getMainRect()->removeChild(upgradeGroup);
        upgradeGroup.reset();

        cachedTower = ProduceTower(towerName, cachedTower->getTileMapManager(), cachedTower->getSprite()->getDrawPriority());

        if (cachedTower == nullptr)
        {
            return false;
        }
//TODO: убедиться в том, что башня реально заменяется без неопределенного поведения
        parentGameScene->replaceObject(oldcached, cachedTower);

        cachedTower.reset();

        if (gameScene != nullptr)
        {
            gameScene->setGameSceneStatus(Enums::GameSceneStatuses::Default);
        }

        return true;
    }

    return false;
}

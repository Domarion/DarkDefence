#include "TowerUpgradeController.h"
#include "../GlobalScripts/GameModel.h"
#include "../GraphicsSystem/UI/CompositeLabel.h"
#include <iostream>
#include "../Input/InputDispatcher.h"
#include "../GraphicsSystem/UI/GroupBox.h"

TowerUpgradeController::TowerUpgradeController()
    :parentGameScene(nullptr), arialFont1(new CFont()), cachedTower(nullptr), fabric(new TowerFabric())
{


}

TowerUpgradeController::~TowerUpgradeController()
{
    delete fabric;
}

void TowerUpgradeController::init(Scene *parent)
{
    parentGameScene = parent;
    arialFont1.get()->loadFromFile("Fonts/arial.ttf", 20);

}

void TowerUpgradeController::receiveTowerUpgrade(Tower *tower)
{
    if (tower == nullptr || parentGameScene == nullptr)
        return;


    std::cout << "TOWER" << std::endl;
    cachedTower = tower;


    string towerName = tower->getName();
    TreeNode<MobModel>* currentGrade = GameModel::getInstance()->getRootTower()->recursiveSearch(towerName);
    if (currentGrade == nullptr || currentGrade->hasChildren() == false)
        return;

    towerMenu.clear();
      std::cout << "TOWER2" << std::endl;


    currentTowerChildrenNames = currentGrade->getChildrenNames();

    auto currentTowerChildren = currentGrade->getChildren();

    towerMenu.initScrollList(currentTowerChildrenNames.size() + 1, 300, 100);
    towerMenu.setRect(200, 100, 300, 600);

    const int iconWidth = 48;
    const int iconWidthSmall = 22;

    for(auto& childrenName: currentTowerChildrenNames)//TODO:new UI View for upgrades
    {
        MobModel childModel = currentTowerChildren.at(childrenName).getData();

        GroupBox* menuItem = new GroupBox();
        towerMenu.addItem(menuItem);
        CTexture* upgradeIcon = new CTexture(iconWidth, iconWidth);
        string iconPath = "GameData/textures/Towers/UpgradeIcons/" + childrenName +".jpg";
        upgradeIcon->loadTexture(iconPath);
        menuItem->addChild(upgradeIcon);


        Label* upgradeName = new Label(childrenName, arialFont1);
        menuItem->addChild(upgradeName);

        GroupBox* priceLabels= new GroupBox();
        menuItem->addChild(priceLabels, true);

        int* childPrice = childModel.getPrice();
        const size_t priceCount = ResourcesModel::resourceTypeCount;
        for(size_t i = 0; i < priceCount; ++i)
        {
            CTexture* resourceIcon = new CTexture(iconWidthSmall, iconWidthSmall);

            string RiconPath = "GameData/textures/Resources/"
                    + GameModel::getInstance()->getResourcesModel()->getResourceNameFromIndex(i) + ".png";
            resourceIcon->loadTexture(RiconPath);
            priceLabels->addChild(resourceIcon);

            Label* resourceLabel = new Label(std::to_string(childPrice[i]), arialFont1);
            priceLabels->addChild(resourceLabel);
        }


        //attack damage, distance, reloadTime, abilities, UPprices

    }


    CTexture* closeButton = new CTexture(iconWidth, iconWidth);
    towerMenu.addItem(closeButton);
    string iconPath = "GameData/textures/Towers/UpgradeIcons/CloseLabel.png";
    closeButton->loadTexture(iconPath);




    if (parentGameScene != nullptr)
    {
          std::cout << "TOWER != nullptr" << std::endl;

        towerMenu.calculateVisibleItemsPositions();
        towerMenu.ConnectMethod(std::bind(&TowerUpgradeController::menuClickHandler, this, std::placeholders::_1));

        parentGameScene->addToUIList(&towerMenu);
    }
}

bool TowerUpgradeController::menuClickHandler(size_t itemIndex)
{


    if (parentGameScene == nullptr || cachedTower == nullptr)
        return false;

    if (itemIndex == currentTowerChildrenNames.size())
    {
        parentGameScene->removeFromUIList(&towerMenu);
        return false;
    }

    std::cout << "itemIndex = " << itemIndex << std::endl;
    string towerName = currentTowerChildrenNames[itemIndex];
    std::cout << "towername = " << towerName << std::endl;

    TreeNode<MobModel>* rootTower = GameModel::getInstance()->getRootTower();
    if (rootTower == nullptr)
    {
        std::cout << "rootTower is nullptr" << std::endl;
        return false;

    }
    TreeNode<MobModel>* searchresult = rootTower->recursiveSearch(towerName);
    if (searchresult == nullptr)
    {
        std::cout << "searchresult is nullptr" << std::endl;
        return false;
    }
    MobModel model(searchresult->getData());




    if (GameModel::getInstance()->getResourcesModel()->canBuy(model.getPrice()))
    {

        GameModel::getInstance()->getResourcesModel()->removeResources(model.getPrice());

        int x = cachedTower->getSprite()->getRect().x;
        int y = cachedTower->getSprite()->getRect().y;
        parentGameScene->destroyObject(cachedTower);

        parentGameScene->removeFromUIList(&towerMenu);

        cachedTower = fabric->produceTower(towerName, this, cachedTower->getTileMapManager());
        if (cachedTower == nullptr)
            return false;
        parentGameScene->spawnObject(x, y, cachedTower);

        cachedTower = nullptr;

        return true;

    }
    else
        std::cout << "CantBuy" << std::endl;

    return false;
}

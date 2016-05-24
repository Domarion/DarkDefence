#include "TowerUpgradeController.h"
#include "../GlobalScripts/GameModel.h"
#include "../GraphicsSystem/UI/CompositeLabel.h"
#include <iostream>
#include "../Input/InputDispatcher.h"

TowerUpgradeController::TowerUpgradeController()
    :parentGameScene(nullptr), arialFont1(), cachedTower(nullptr), fabric(new TowerFabric())
{


}

TowerUpgradeController::~TowerUpgradeController()
{
    delete fabric;
}

void TowerUpgradeController::init(Scene *parent)
{
    parentGameScene = parent;
     arialFont1.loadFromFile("Fonts/arial.ttf", 20);

}

void TowerUpgradeController::receiveTowerUpgrade(Tower *tower, int x, int y)
{
    if (tower == nullptr || parentGameScene == nullptr)
        return;


    std::cout << "TOWER" << std::endl;
    cachedTower = tower;
    string towerName = tower->getName();
    TreeNode<MobModel>* currentGrade = GameModel::getInstance()->getRootTower()->recursiveSearch(towerName);
    if (currentGrade == nullptr)
        return;
      std::cout << "TOWER2" << std::endl;
    currentTowerChildren = currentGrade->getChildrenNames();
    towerMenu.initScrollList(currentTowerChildren.size(), 150, 48);
    towerMenu.setRect(tower->getSprite()->getRect().x + 150, tower->getSprite()->getRect().y, 300, 400);
      std::cout << "TOWER_MENU_POS x = " << (towerMenu.getRect().x) << " y = " << (towerMenu.getRect().y) << std::endl;

      for(size_t i = 0; i < currentTowerChildren.size(); ++i)
    {
        CompositeLabel* label = new CompositeLabel();
        label->setFont(arialFont1);
        string iconPath = "GameData/textures/Towers/UpgradeIcons/" + currentTowerChildren[i] +".jpg";
        std::cout << iconPath << std::endl;
        label->loadIcon(iconPath);
        label->setIconRect(0,0, 48, 48);
        //label->setPos(0,0);
        label->setText(currentTowerChildren[i]);

        std::cout << "LabelText= " << (label->getText()) << std::endl;
        towerMenu.addItem(label);
    }
    if (parentGameScene != nullptr)
    {
          std::cout << "TOWER != nullptr" << std::endl;

        towerMenu.calculateVisibleItemsPositions();
        towerMenu.ConnectMethod(std::bind(&TowerUpgradeController::menuClickHandler, this, std::placeholders::_1));

        parentGameScene->addToUIList(&towerMenu);
        InputDispatcher::getInstance()->addHandler(&towerMenu);
    }
}

bool TowerUpgradeController::menuClickHandler(int itemIndex)
{


    if (parentGameScene == nullptr || cachedTower == nullptr)
        return false;
    string towerName = currentTowerChildren[itemIndex];
    MobModel model = GameModel::getInstance()->getRootTower()->recursiveSearch(towerName)->getData();




    if (GameModel::getInstance()->getResourcesModel()->canBuy(model.getPrice()))
    {

        GameModel::getInstance()->getResourcesModel()->removeResources(model.getPrice());

        int x = cachedTower->getSprite()->getRect().x;
        int y = cachedTower->getSprite()->getRect().y;
        parentGameScene->destroyObject(cachedTower);

        cachedTower = fabric->produceTower(towerName, this);
        if (cachedTower == nullptr)
            return false;
        parentGameScene->spawnObject(x, y, cachedTower);
        parentGameScene->removeFromUIList(&towerMenu);
        InputDispatcher::getInstance()->removeHandler(&towerMenu);
        // cachedTower = nullptr;

    return true;

    }
    else
        std::cout << "CantBuy" << std::endl;
    return false;


}

#include "TowerUpgradeController.h"
#include "../GlobalScripts/GameModel.h"
#include "../GraphicsSystem/UI/CompositeLabel.h"
#include <iostream>
#include "../Input/InputDispatcher.h"

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


    currentTowerChildren = currentGrade->getChildrenNames();


    std::cout << "TOWERupCHILDREN SIZE = " << (currentTowerChildren.size()) << std::endl;
    towerMenu.initScrollList(currentTowerChildren.size() + 1, 150, 48);
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

    CompositeLabel* closeLabel = new CompositeLabel();
    closeLabel->setFont(arialFont1);
    string iconPath = "GameData/textures/Towers/UpgradeIcons/CloseLabel.png";
    std::cout << iconPath << std::endl;
    closeLabel->loadIcon(iconPath);
    closeLabel->setIconRect(0,0, 48, 48);
    //label->setPos(0,0);
    closeLabel->setText("Close");
    towerMenu.addItem(closeLabel);




    if (parentGameScene != nullptr)
    {
          std::cout << "TOWER != nullptr" << std::endl;

        towerMenu.calculateVisibleItemsPositions();
        towerMenu.ConnectMethod(std::bind(&TowerUpgradeController::menuClickHandler, this, std::placeholders::_1));

        parentGameScene->addToUIList(&towerMenu);
        InputDispatcher::getInstance()->addHandler(&towerMenu);
    }
}

bool TowerUpgradeController::menuClickHandler(size_t itemIndex)
{


    if (parentGameScene == nullptr || cachedTower == nullptr)
        return false;

    if (itemIndex == currentTowerChildren.size())
    {
        parentGameScene->removeFromUIList(&towerMenu);
        InputDispatcher::getInstance()->removeHandler(&towerMenu);
        return false;
    }

    std::cout << "itemIndex = " << itemIndex << std::endl;
    string towerName = currentTowerChildren[itemIndex];
    MobModel model = GameModel::getInstance()->getRootTower()->recursiveSearch(towerName)->getData();




    if (GameModel::getInstance()->getResourcesModel()->canBuy(model.getPrice()))
    {

        GameModel::getInstance()->getResourcesModel()->removeResources(model.getPrice());

        int x = cachedTower->getSprite()->getRect().x;
        int y = cachedTower->getSprite()->getRect().y;
           InputDispatcher::getInstance()->removeHandler(cachedTower);
        parentGameScene->destroyObject(cachedTower);

        parentGameScene->removeFromUIList(&towerMenu);
        InputDispatcher::getInstance()->removeHandler(&towerMenu);

        cachedTower = fabric->produceTower(towerName, this);
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

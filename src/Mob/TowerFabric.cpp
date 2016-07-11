#include "TowerFabric.hpp"
#include "../GraphicsSystem/CTexture.h"
#include "../GlobalScripts/GameModel.h"

TowerFabric::TowerFabric()
{

}

TowerFabric::~TowerFabric()
{
   /* for(size_t i = 0; i < producedTowers.size(); ++i)
    {
        delete producedTowers[i];
        producedTowers[i] = nullptr;
    }*/
    producedTowers.clear();
}

Tower * TowerFabric::produceTower(std::string towerName, TowerUpgradeController* upgrader)
{
    MobModel* model = GameModel::getInstance()->getTowerByName(towerName);
    if (model == nullptr)
        return nullptr;
    Tower* someMob = new Tower(model);
    AnimatedSprite* someSprite = new AnimatedSprite();

    someSprite->setRect(0,0, 50, 80);
    someSprite->loadTexture("GameData/textures/Towers/" + towerName + ".png");

    someMob->setSprite(someSprite);


    if (upgrader != nullptr)
        someMob->connectMethod(std::bind(&TowerUpgradeController::receiveTowerUpgrade, upgrader, std::placeholders::_1));
    someMob->init(0, 0);

    producedTowers.push_back(someMob);

    return someMob;
}

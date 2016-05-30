#include "TowerFabric.hpp"
#include "../GraphicsSystem/CTexture.h"
#include "../GlobalScripts/GameModel.h"

TowerFabric::TowerFabric()
{

}

TowerFabric::~TowerFabric()
{
    for(int i = 0; i < producedTowers.size(); ++i)
        delete producedTowers[i];
}

Tower * TowerFabric::produceTower(std::string towerName, TowerUpgradeController* upgrader)
{
    MobModel* model = GameModel::getInstance()->getTowerByName(towerName);
    if (model == nullptr)
        return nullptr;
    Tower* someMob = new Tower(model);
    CTexture* someSprite = new CTexture();

    someSprite->setRect(0,0, 50, 80);
    someSprite->loadTexture("GameData/textures/Towers/" + towerName + ".png");

    someMob->setSprite(someSprite);


    if (upgrader != nullptr)
        someMob->connectMethod(std::bind(&TowerUpgradeController::receiveTowerUpgrade, upgrader, std::placeholders::_1, 0 ,0 ));
    someMob->init();

    producedTowers.push_back(someMob);

    return someMob;
}

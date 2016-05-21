#include "TowerFabric.hpp"
#include "../GraphicsSystem/Sprite.h"
#include "../GlobalScripts/GameModel.h"

TowerFabric::TowerFabric()
{

}

Tower * const TowerFabric::produceTower(std::string towerName, TowerUpgradeController* upgrader)
{
    MobModel* model = GameModel::getInstance()->getTowerByName(towerName);
    if (model == nullptr)
        return nullptr;
    Tower* someMob = new Tower(model);
    Sprite* someSprite = new Sprite();

    someSprite->setRect(0,0, 50, 80);
    someSprite->setTexture(Renderer::getInstance()->loadTextureFromFile("/home/kostya_hm/Projects/DarkDefence/GameData/textures/Towers/" + towerName + ".png"));

    someMob->setSprite(someSprite);


    if (upgrader != nullptr)
        someMob->connectMethod(std::bind(&TowerUpgradeController::receiveTowerUpgrade, upgrader, std::placeholders::_1, 0 ,0 ));
    someMob->init();
    return someMob;
}

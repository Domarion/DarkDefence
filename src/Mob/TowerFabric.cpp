#include "TowerFabric.hpp"
#include "../GraphicsSystem/Sprite.h"
#include "../GlobalScripts/GameModel.h"
TowerFabric::TowerFabric()
{

}

Mob * const TowerFabric::produceTower(std::string towerName)
{
    MobModel* model = GameModel::getInstance()->getTowerByName(towerName);

    Mob* someMob = new Mob(model);
    Sprite* someSprite = new Sprite();

    someSprite->setRect(0,0, 50, 80);
    someSprite->setTexture(Renderer::getInstance()->loadTextureFromFile("/home/kostya_hm/Projects/DarkDefence/GameData/textures/Towers/" + towerName + ".png"));

    someMob->setSprite(someSprite);
    someMob->init();
    return someMob;
}

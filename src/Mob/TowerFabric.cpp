#include "TowerFabric.hpp"
#include "../GraphicsSystem/Sprite.h"
TowerFabric::TowerFabric()
{

}

Mob * const TowerFabric::produceTower(std::string towerName, SDL_Renderer* renderer)
{
    MobModel* model = GameModel::getInstance()->getTowerByName(towerName);

    Mob* someMob = new Mob(model);
    Sprite* someSprite = new Sprite();
    someSprite->setRenderer(renderer);
    someSprite->setRect(new SDL_Rect({0,0, 50, 80}));
    someSprite->loadTextureFromFile("/home/kostya_hm/Projects/DarkDefence/GameData/textures/Towers/" + towerName + ".png");
    someMob->setSprite(someSprite);
    someMob->init();
    return someMob;
}

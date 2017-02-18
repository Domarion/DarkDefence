#include "TowerFabric.hpp"
#include "../GlobalScripts/GameModel.h"
#include "../GlobalScripts/ResourceManager.h"
std::shared_ptr<Tower> TowerFabric::produceTower(
        std::string towerName,
        std::shared_ptr<RenderingSystem>& aRenderingContext,
        std::shared_ptr<TowerUpgradeController> upgrader,
        std::shared_ptr<TileMapManager> aTileMap)
{
    auto model = GameModel::getInstance()->getTowerByName(towerName);
    if (model == nullptr)
        return nullptr;
    auto someMob = std::make_shared<Tower>(std::move(model), aTileMap);
    auto someSprite = std::make_shared<AnimationSceneSprite>(aRenderingContext);


    someSprite->setTexture(ResourceManager::getInstance()->getTexture(towerName));
//    someSprite->setSize(Size(50, 80));
//    someSprite->loadTexture("GameData/textures/Towers/" + towerName + ".png");

    someMob->setSprite(someSprite);

    if (upgrader != nullptr)
        someMob->connectMethod(std::bind(&TowerUpgradeController::receiveTowerUpgrade, upgrader, std::placeholders::_1));

    someMob->init(0, 0);


    return someMob;
}

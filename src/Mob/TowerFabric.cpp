#include "TowerFabric.hpp"
#include "../GraphicsSystem/CTexture.h"
#include "../GlobalScripts/GameModel.h"

std::shared_ptr<Tower> TowerFabric::produceTower(
        std::string towerName,
        std::shared_ptr<RenderingSystem>& aRenderingContext,
        std::shared_ptr<TowerUpgradeController> upgrader,
        TileMapManager* aTileMap)
{
    MobModel* model = GameModel::getInstance()->getTowerByName(towerName);
    if (model == nullptr)
        return nullptr;
    auto someMob = std::make_shared<Tower>(model, aTileMap);
    auto someSprite = std::make_shared<AnimationSceneSprite>(aRenderingContext);


    someSprite->setSize(Size(50, 80));
    someSprite->loadTexture("GameData/textures/Towers/" + towerName + ".png");

    someMob->setSprite(someSprite);

    if (upgrader != nullptr)
        someMob->connectMethod(std::bind(&TowerUpgradeController::receiveTowerUpgrade, upgrader, std::placeholders::_1));

    someMob->init(0, 0);


    return someMob;
}

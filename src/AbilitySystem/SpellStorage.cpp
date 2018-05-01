#include "SpellStorage.h"
#include "../AbilitySystem/AbilityMagicStones.h"
#include "../AbilitySystem/AbilitySnowStorm.h"
#include "../AbilitySystem/AbilityShrink.h"
//#include "../AbilitySystem/AbilityPrick.h"
#include "../AbilitySystem/AbilityEarthquake.h"
//#include "../AbilitySystem/AbilityMagicBlink.h"
#include "../AbilitySystem/AbilityObjectSpawn.h"
#include "../AbilitySystem/PrickObject.h"
#include "../AbilitySystem/BlinkObject.h"

void SpellStorage::loadWithScene(std::shared_ptr<Scene> scenePtr, const std::shared_ptr<ManaGlobal>& aManaModel)
{
    auto magicStones = std::make_unique<AbilityMagicStones>(aManaModel);
    magicStones->init(scenePtr);
    magicStones->setManaCost(100);
    magicStones->setCooldownTime(10000);
    magicStones->setWorkTime(10000);

    auto snowStorm = std::make_unique<AbilitySnowStorm>(aManaModel);
    snowStorm->init(scenePtr);
    snowStorm->setManaCost(50);
    snowStorm->setCooldownTime(10000);
    snowStorm->setWorkTime(10000);
    snowStorm->setDamagePerSecond(30);

    auto shrink = std::make_unique<AbilityShrink>(aManaModel);
    shrink->init(scenePtr);
    shrink->setManaCost(100);
    shrink->setCooldownTime(20000);
    shrink->setWorkTime(11000);
    shrink->setDamagePerSecond(0.2);

    // TODO добавить анимацию для Prick.
    auto prick = std::make_unique<AbilityObjectSpawn<PrickObject>>(aManaModel);
    prick->init(scenePtr);
    prick->setManaCost(100);
    prick->setCooldownTime(10000);
    prick->setWorkTime(0);
    prick->setDamage(400);
    prick->setAbilityName("AbilityPrick");

    auto quake = std::make_unique<AbilityEarthquake>(aManaModel);
    quake->init(scenePtr);
    quake->setManaCost(50);
    quake->setCooldownTime(10000);
    quake->setWorkTime(3000);
    quake->setDamagePerSecond(30);

    auto magicBlink = std::make_unique<AbilityObjectSpawn<BlinkObject>>(aManaModel);
    magicBlink->init(scenePtr);
    magicBlink->setManaCost(50);
    magicBlink->setCooldownTime(10000);
    magicBlink->setWorkTime(0);
    magicBlink->setDamage(1000);
    magicBlink->setAbilityName("AbilityMagicBlink");

    abilityModelsMap["MagicStones"] = std::move(magicStones);
    abilityModelsMap["SnowStorm"] = std::move(snowStorm);
    abilityModelsMap["Shrink"] = std::move(shrink);
    abilityModelsMap["Prick"] = std::move(prick);
    abilityModelsMap["Earthquake"] = std::move(quake);
    abilityModelsMap["MagicBlink"] = std::move(magicBlink);
}

const std::shared_ptr<AbilityModel>& SpellStorage::getAbilityModelWithName(const std::string& aName)
{
    return abilityModelsMap.at(aName);
}

bool SpellStorage::setAbilityReady(const string& aAbilityName)
{
    return abilityModelsMap.at(aAbilityName)->trySetAsReady();
}

void SpellStorage::updateAbilities(double aTimeStep)
{
    for(auto& abilityPair : abilityModelsMap)
    {
        if (abilityPair.second != nullptr)
        {
            (abilityPair.second)->update(aTimeStep);
        }
    }
}

const std::map<std::string, std::shared_ptr<AbilityModel>>& SpellStorage::getAbilityModelList() const
{
    return abilityModelsMap;
}

bool SpellStorage::canPlaceObjectAbility(const std::string& aAbilityName) const
{
    return abilityModelsMap.at(aAbilityName)->canPlaceObject();
}

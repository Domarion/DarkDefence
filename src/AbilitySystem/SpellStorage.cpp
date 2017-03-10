#include "SpellStorage.h"
#include "../AbilitySystem/AbilityMagicStones.h"
#include "../AbilitySystem/AbilitySnowStorm.h"
#include "../AbilitySystem/AbilityShrink.h"
#include "../AbilitySystem/AbilityPrick.h"
#include "../AbilitySystem/AbilityEarthquake.h"
#include "../AbilitySystem/AbilityMagicBlink.h"

SpellStorage::SpellStorage()
{

}

SpellStorage::~SpellStorage()
{
    free();
}

void SpellStorage::loadWithScene(std::shared_ptr<Scene> scenePtr, std::shared_ptr<ManaGlobal> aManaModel)
{
    auto magicStones = std::make_unique<AbilityMagicStones>(aManaModel);
    magicStones->init(scenePtr);
    magicStones->setManaCost(100);
    magicStones->setCooldownTime(10000);
    magicStones->setWorkTime(10000);


    auto snowStorm = std::make_unique<AbilitySnowStorm>(aManaModel);
    snowStorm->init(scenePtr);
    snowStorm->setManaCost(100);
    snowStorm->setCooldownTime(10000);
    snowStorm->setWorkTime(10000);
    snowStorm->setDamagePerSecond(30);

    auto shrink = std::make_unique<AbilityShrink>(aManaModel);

    shrink->init(scenePtr);
    shrink->setManaCost(100);
    shrink->setCooldownTime(20000);
    shrink->setWorkTime(11000);
    shrink->setDamagePerSecond(0.2);

    auto prick = std::make_unique<AbilityPrick>(aManaModel);
    prick->init(scenePtr);
    prick->setManaCost(100);
    prick->setCooldownTime(10000);
    prick->setWorkTime(0);
    prick->setDamage(120);

    auto quake = std::make_unique<AbilityEarthquake>(aManaModel);
    quake->init(scenePtr);
    quake->setManaCost(50);
    quake->setCooldownTime(10000);
    quake->setWorkTime(3000);
    quake->setDamagePerSecond(30);


    auto magicBlink = std::make_unique<AbilityMagicBlink>(aManaModel);
    magicBlink->init(scenePtr);
    magicBlink->setManaCost(50);
    magicBlink->setCooldownTime(10000);
    magicBlink->setWorkTime(10000);
    magicBlink->setDamage(20);

    abilityModelsMap["MagicStones"] = std::move(magicStones);
    abilityModelsMap["SnowStorm"] = std::move(snowStorm);
    abilityModelsMap["Shrink"] = std::move(shrink);
    abilityModelsMap["Prick"] = std::move(prick);
    abilityModelsMap["Earthquake"] = std::move(quake);
    abilityModelsMap["MagicBlink"] = std::move(magicBlink);

}

std::shared_ptr<AbilityModel> SpellStorage::getAbilityModelWithName(string name)
{
    return abilityModelsMap.at(name);
}

void SpellStorage::setAbilityReady(string s)
{
    abilityModelsMap.at(s)->setAsReady();

}

void SpellStorage::updateAbilities(double timestep)
{
    for(auto ptr0 = abilityModelsMap.begin(); ptr0 != abilityModelsMap.end(); ++ptr0)
        ptr0->second->update(timestep);
}

map<std::string, std::shared_ptr<AbilityModel> > &SpellStorage::getAbilityModelList()
{
     return abilityModelsMap;
}

void SpellStorage::free()
{
    abilityModelsMap.clear();
}

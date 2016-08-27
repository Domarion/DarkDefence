#include "SpellStorage.h"
#include "../AbilitySystem/AbilityMagicStones.h"
#include "../AbilitySystem/AbilitySnowStorm.h"
#include "../AbilitySystem/AbilityShrink.h"
#include "../AbilitySystem/AbilityPrick.h"
#include "../AbilitySystem/AbilityEarthquake.h"

SpellStorage::SpellStorage()
{

}

SpellStorage::~SpellStorage()
{
    free();
}

void SpellStorage::loadWithScene(Scene *scenePtr)
{
    AbilityMagicStones* magicStones = new AbilityMagicStones();

    magicStones->init(scenePtr);
    magicStones->setManaCost(100);
    magicStones->setCooldownTime(10000);
    magicStones->setWorkTime(10000);


    AbilitySnowStorm* snowStorm = new AbilitySnowStorm();
    snowStorm->init(scenePtr);
    snowStorm->setManaCost(100);
    snowStorm->setCooldownTime(10000);
    snowStorm->setWorkTime(10000);
    snowStorm->setDamagePerSecond(30);


    AbilityShrink* shrink = new AbilityShrink();
    shrink->init(scenePtr);
    shrink->setManaCost(100);
    shrink->setCooldownTime(20000);
    shrink->setWorkTime(11000);
    shrink->setDamagePerSecond(0.2);

    AbilityPrick* prick = new AbilityPrick();
    prick->init(scenePtr);
    prick->setManaCost(100);
    prick->setCooldownTime(10000);
    prick->setWorkTime(0);
    prick->setDamage(120);

    AbilityEarthquake* quake = new AbilityEarthquake();
    quake->init(scenePtr);
    quake->setManaCost(50);
    quake->setCooldownTime(10000);
    quake->setWorkTime(3000);
    quake->setDamagePerSecond(30);

    abilityModelsMap["MagicStones"] = magicStones;
    abilityModelsMap["SnowStorm"] = snowStorm;
    abilityModelsMap["Shrink"] = shrink;
    abilityModelsMap["Prick"] = prick;
    abilityModelsMap["Earthquake"] = quake;
}

AbilityModel * SpellStorage::getAbilityModelWithName(string name)
{
    return abilityModelsMap[name];
}

void SpellStorage::setAbilityReady(string s)
{
    abilityModelsMap[s]->setAsReady();

}

void SpellStorage::updateAbilities(double timestep)
{
    for(auto ptr0 = abilityModelsMap.begin(); ptr0 != abilityModelsMap.end(); ++ptr0)
        ptr0->second->update(timestep);
}

map<string, AbilityModel *> &SpellStorage::getAbilityModelList()
{
     return abilityModelsMap;
}

void SpellStorage::free()
{
    for(auto t: abilityModelsMap)
        delete (t.second);

}

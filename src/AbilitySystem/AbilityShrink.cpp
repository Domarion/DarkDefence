#include "AbilityShrink.h"
#include "../GlobalScripts/GameModel.h"
#include "Utility/textfilefunctions.h"
#include "../GlobalScripts/ResourceManager.h"
#include "../Grouping/Scene.h"
#include "Logging/Logger.h"

AbilityShrink::AbilityShrink(std::shared_ptr<ManaGlobal> aManaModel)
    : AbilityModel(aManaModel)
    , damagePerSecond(0.0)
{
}

bool AbilityShrink::onReady(double /*timestep*/)
{
    LOG_INFO("Enter.");

    if (affectedMobs == nullptr && parentScenePtr != nullptr && GameModel::getInstance()->getMonsterCount() > 0)
        affectedMobs = parentScenePtr->findObjectsByTag("Monster");

    if (affectedMobs)
    {
        LOG_INFO("Monsters found.");
        abilityState = Enums::AbilityStates::asWorking;
        spawnEffect(10000);
    }
    else
        abilityState = Enums::AbilityStates::asNotAvaliable;

    return true;
}

bool AbilityShrink::onWorking(double timestep)
{
    if (counter >= 1000)
    {
        if (affectedMobs != nullptr && !affectedMobs->empty())
            for(auto affectedMob = affectedMobs->begin(); affectedMob != affectedMobs->end(); ++affectedMob)
            {
                if (*affectedMob != nullptr && (*affectedMob)->getDestructibleObject() != nullptr)
                {
                    int damage = static_cast<int>((*affectedMob)->getDestructibleObject()->getMaximumHealth()*damagePerSecond);
                    (*affectedMob)->getDestructibleObject()->receiveDamageOneType(3, damage);
                }
            }
        counter = 0;
    }

    if (currentWorkTime <= 0)
    {
        currentWorkTime = workTime;
        abilityState = Enums::AbilityStates::asOnCooldown;
        affectedMobs.reset();
    }
    else
    {
        currentWorkTime -= timestep;
        counter+= timestep;
    }

    return true;
}

void AbilityShrink::setDamagePerSecond(double value)
{
    damagePerSecond = value;
}

double AbilityShrink::getDamagePerSecond() const
{
    return damagePerSecond;
}

void AbilityShrink::spawnEffect(double timeToLive)
{
    spellAnimationObject = std::make_shared<AbilityAnimObject>(timeToLive);

    std::string abName = "Shrink";
    auto& animPack = ResourceManager::getInstance()->getAnimationPack(abName);
    auto someSprite = std::make_shared<AnimationSceneSprite>(
        parentScenePtr->getRenderer(), AnimationSceneSprite::Animation{animPack});

    someSprite->setTexture(ResourceManager::getInstance()->getTexture(abName));

    spellAnimationObject->setSprite(someSprite);
    // TODO: Remove Hardcode.
    someSprite->setCurrentState("cast");
    parentScenePtr->spawnObject(Position(100, 100), spellAnimationObject);
}

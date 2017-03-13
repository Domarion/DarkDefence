#include "AbilityShrink.h"
#include "../GlobalScripts/GameModel.h"
#include "Utility/textfilefunctions.h"
AbilityShrink::AbilityShrink(std::shared_ptr<ManaGlobal> aManaModel)
    : AbilityModel(aManaModel)
    , damagePerSecond(0.0)
    , affectedMobs( nullptr )
    , spellAnimationObject(nullptr)
{

}

AbilityShrink::~AbilityShrink()
{

}

void AbilityShrink::init(std::shared_ptr<Scene> scenePtr)
{
    AbilityModel::init(scenePtr);
}

bool AbilityShrink::onReady(double timestep)
{
    if (AbilityModel::onReady(timestep) == false)
    {
        abilityState = Enums::AbilityStates::asNotAvaliable;

        return false;
    }


    if (affectedMobs == nullptr && parentScenePtr != nullptr && GameModel::getInstance()->getMonsterCount() > 0)
        affectedMobs = parentScenePtr->findObjectsByTag("Monster");

    if (affectedMobs != nullptr)
    {
        std::cout << "Shrink working" << std::endl;
        abilityState = Enums::AbilityStates::asWorking;
        spawnEffect(10000);
    }
    else
        abilityState = Enums::AbilityStates::asNotAvaliable;

    return true;
}

bool AbilityShrink::onWorking(double timestep)
{
    static double counter = 0.0;

    if (counter >= 1000)
    {
        if (affectedMobs != nullptr && affectedMobs->size() > 0)
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
        affectedMobs->clear();
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
    auto someSprite = std::make_shared<AnimationSceneSprite>(parentScenePtr->getRenderer());


    someSprite->setSize(Size( 300, 300));
    someSprite->loadTexture("GameData/textures/SpellAnims/AbilityShrink.png");

    std::map<std::string, std::vector<SDL_Rect> > anims;

    std::string filename = "GameData/anims/Spells/AbilityShrink.anim";
    androidText::setRelativePath(filename);
    androidText::loadAnimFromFile(filename, anims);

    for(auto& anim : anims)
    {
        someSprite->setAnimRects(anim.first, anim.second);
    }
    spellAnimationObject->setSprite(someSprite);
    parentScenePtr->spawnObject(100, 100, spellAnimationObject);
    someSprite->setCurrentState("cast");

}


/*	short formula = (short)(ef.getHealthMax()*DamageValuePerSecond);
                        //DebugMap.Instance.AddMessage("\nDamageValuePerSecond" + DamageValuePerSecond.ToString());
                        ef.ReceiveDamageOneType(formula,(byte)DamageTypes.Psionical,false);
                        */

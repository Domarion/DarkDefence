#include "AbilityAnimObject.hpp"
#include "Utility/textfilefunctions.h"
#include "GlobalScripts/ResourceManager.h"

AbilityAnimObject::AbilityAnimObject(double timeToLiveSec)
    : SceneObject()
    , mTimeToLive(timeToLiveSec)
{

}

bool AbilityAnimObject::update(double timestep)
{
    if (mTimeToLive < 0)
    {
        return false;
    }

    mTimeToLive -= timestep;
    return SceneObject::update(timestep);
;
}

std::shared_ptr<AbilityAnimObject> Make_AbilityAnimObject(
    const std::string& aName,
    double aTimeToLiveMs,
    std::shared_ptr<RenderingSystem>& aRenderer)
{
    auto object = std::make_shared<AbilityAnimObject>(aTimeToLiveMs);
    if (object == nullptr)
    {
        return nullptr;
    }

    auto& animPack = ResourceManager::getInstance()->getAnimationPack(aName);
    auto sprite = std::make_shared<AnimationSceneSprite>(aRenderer, AnimationSceneSprite::Animation{animPack});

    if (sprite == nullptr)
    {
        return nullptr;
    }

    sprite->setTexture(ResourceManager::getInstance()->getTexture(aName));

    object->setSprite(sprite);

    return object;
}

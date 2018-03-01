#include <limits>

#include "AbilityAnimObject.hpp"
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
}

bool AbilityAnimObject::isFinished() const
{
    return static_cast<int>(mTimeToLive) <= 0 || abs(mTimeToLive) < std::numeric_limits<double>::epsilon();
}

std::shared_ptr<AbilityAnimObject> Make_AbilityAnimObject(
    const std::string& aName,
    double aTimeToLiveMs,
    std::shared_ptr<RenderingSystem>& aRenderer,
    size_t aDrawPriority)
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
    object->setDrawPriority(aDrawPriority);

    return object;
}

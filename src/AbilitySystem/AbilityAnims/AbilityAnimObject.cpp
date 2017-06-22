#include "AbilityAnimObject.hpp"
#include "Utility/textfilefunctions.h"

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
    const std::string& aNameWithParentDir,
    Size aImageSize,
    double aTimeToLiveMs,
    std::shared_ptr<RenderingSystem>& aRenderer)
{
    auto object = std::make_shared<AbilityAnimObject>(aTimeToLiveMs);
    if (object == nullptr)
    {
        return nullptr;
    }
    auto sprite = std::make_shared<AnimationSceneSprite>(aRenderer);

    if (sprite == nullptr)
    {
        return nullptr;
    }

    std::string textureFullPath {"GameData/textures/"};
    textureFullPath.append(aNameWithParentDir);
    textureFullPath.append(".png");

    sprite->loadTexture(textureFullPath);
    sprite->setSize(aImageSize);

    std::string animPath {"GameData/anims/"};
    animPath.append(aNameWithParentDir);
    animPath.append(".anim");

    androidText::setRelativePath(animPath);

    map<string, vector<SDL_Rect> > anims;
    androidText::loadAnimFromFile(animPath, anims);

    for(auto& anim : anims)
    {
        sprite->setAnimRects(anim.first, anim.second);
    }

    object->setSprite(sprite);

    return object;

}

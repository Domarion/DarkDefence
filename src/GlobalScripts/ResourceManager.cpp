#include "ResourceManager.h"
#include <cereal/archives/xml.hpp>
#include <vector>
#include <cereal/access.hpp>
#include <cereal/types/vector.hpp>
#include <sstream>
#include "../Utility/TextureData.hpp"
#include "../Utility/textfilefunctions.h"


ResourceManager* ResourceManager::mInstance = nullptr;

ResourceManager* ResourceManager::getInstance()
{
    if (mInstance == nullptr)
    {
        mInstance = new ResourceManager();
    }

    return mInstance;
}

void ResourceManager::loadConfigFromFile(
    const std::string& aFilename, std::shared_ptr<RenderingSystem> aRenderingSystem)
{
    if (!mNameToTextureMap.empty())
    {
        return;
    }

    string textString;
    androidText::loadTextFileToString(aFilename, textString);

    if (!textString.empty())
    {
        std::vector<UtilityStruct::Res> configs;
        std::stringstream str(textString);

        cereal::XMLInputArchive xmlinp(str);

        xmlinp(configs);

        for (const auto& config : configs)
        {
            Texture2D texture(aRenderingSystem);
            texture.loadTexture(config.ImagePath);
            texture.setSize(config.ImageSize);
            mNameToTextureMap[config.Caption] = texture;

            if (!config.AnimationPackPath.empty())
            {
                auto animPack = loadAnimationPack(config.AnimationPackPath);
                mAnimationCollection.emplace(config.Caption, std::move(animPack));
            }
        }
    }
}

Texture2D ResourceManager::getTexture(const std::string& aObjectName) const
{
    return mNameToTextureMap.at(aObjectName);
}

const ResourceManager::AnimationPack& ResourceManager::getAnimationPack(const std::string& aAnimationPackName) const
{
    return mAnimationCollection.at(aAnimationPackName);
}

bool ResourceManager::hasAnimationPack(const std::string& aAnimationPackName) const
{
    if (mAnimationCollection.empty())
    {
        return false;
    }

    return mAnimationCollection.find(aAnimationPackName) != mAnimationCollection.cend();
}

bool ResourceManager::hasTexture(const std::string& aObjectName) const
{
    if (mNameToTextureMap.empty())
    {
        return false;
    }

    return mNameToTextureMap.find(aObjectName) != mNameToTextureMap.cend();
}

ResourceManager::AnimationPack ResourceManager::loadAnimationPack(const std::string& aAnimationPackPath)
{
    ResourceManager::AnimationPack animPack;
    androidText::loadAnimFromFile(aAnimationPackPath, animPack);

    return animPack;
}

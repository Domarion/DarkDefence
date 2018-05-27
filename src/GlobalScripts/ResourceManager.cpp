#include <sstream>

#include <cereal/archives/xml.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>

#include "ResourceManager.h"
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

void ResourceManager::loadAudioConfigFromFile(const std::string& aFilename)
{
    if (!mSounds.empty() || !mMusicCollection.empty())
    {
        return;
    }

    string textString;
    androidText::loadTextFileToString(aFilename, textString);

    if (!textString.empty() || (textString.size() == 1 && textString[0] == '\n'))
    {
        std::vector<UtilityStruct::ResAudio> configs;
        std::stringstream str(textString);

        cereal::JSONInputArchive jsonInput(str);

        jsonInput(configs);
        for (const auto& config : configs)
        {
            if (config.AudioType == UtilityStruct::ResAudio::TAudioType::Sound)
            {
                Sound s;
                s.loadSound(config.Path);
                mSounds.emplace(config.Caption, std::move(s));
            }
            else
            {
                Music mus;
                mus.loadMusic(config.Path);
                mMusicCollection.emplace(config.Caption, std::move(mus));
            }
        }
    }
}

const Texture2D& ResourceManager::getTexture(const std::string& aObjectName) const
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

bool ResourceManager::hasSound(const std::string& aObjectName) const
{
    return mSounds.find(aObjectName) != mSounds.cend();
}

bool ResourceManager::hasMusic(const std::string& aObjectName) const
{
    return mMusicCollection.find(aObjectName) != mMusicCollection.cend();
}

const Sound& ResourceManager::getSound(const std::string& aObjectName) const
{
    return mSounds.at(aObjectName);
}

const Music& ResourceManager::getMusic(const std::string& aObjectName) const
{
    return mMusicCollection.at(aObjectName);
}

ResourceManager::AnimationPack ResourceManager::loadAnimationPack(const std::string& aAnimationPackPath)
{
    ResourceManager::AnimationPack animPack;
    androidText::loadAnimFromFile(aAnimationPackPath, animPack);

    return animPack;
}

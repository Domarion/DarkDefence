#pragma once

#include <map>
#include <vector>

#include "../GraphicsSystem/newSystem/Texture2D.h"
#include "../AudioSystem/Music.hpp"
#include "../AudioSystem/Sound.hpp"

struct ResourceManager
{
public:
    using AnimationPack = std::map<string, std::vector<SDL_Rect>>;
    using AnimationCollection = std::map<std::string, AnimationPack>;
    using SoundCollection = std::map<std::string, Sound>;
    using MusicCollection = std::map<std::string, Music>;

    static ResourceManager* getInstance();

    void loadConfigFromFile(
        const std::string& aFilename,
        std::shared_ptr<RenderingSystem> aRenderingSystem);
    void loadAudioConfigFromFile(const std::string& aFilename);

    const Texture2D& getTexture(const std::string& aObjectName) const;
    const AnimationPack& getAnimationPack(const std::string& aAnimationPackName) const;
    bool hasAnimationPack(const std::string& aAnimationPackName) const;
    bool hasTexture(const std::string& aObjectName) const;

    bool hasSound(const std::string& aObjectName) const;
    bool hasMusic(const std::string& aObjectName) const;
    const Sound& getSound(const std::string& aObjectName) const;
    const Music& getMusic(const std::string& aObjectName) const;
private:

    AnimationPack loadAnimationPack(const std::string& aAnimationPackPath);
    std::map<std::string, Texture2D> mNameToTextureMap;
    AnimationCollection mAnimationCollection;

    SoundCollection mSounds;
    MusicCollection mMusicCollection;

    ResourceManager() = default;
    ~ResourceManager() = default;
    static ResourceManager* mInstance;
};


#pragma once

#include "../GraphicsSystem/newSystem/Texture2D.h"
#include <map>
#include <vector>

struct ResourceManager
{
public:
    using AnimationPack = std::map<string, std::vector<SDL_Rect>>;
    using AnimationCollection = std::map<std::string, AnimationPack>;

    static ResourceManager* getInstance();
    void loadConfigFromFile(
            const std::string& aFilename,
            std::shared_ptr<RenderingSystem> aRenderingSystem);
    Texture2D getTexture(const std::string& aObjectName) const;
    const AnimationPack& getAnimationPack(const std::string& aAnimationPackName) const;
    bool hasAnimationPack(const std::string& aAnimationPackName) const;
    bool hasTexture(const std::string& aObjectName) const;
private:

    AnimationPack loadAnimationPack(const std::string& aAnimationPackPath);
    std::map<std::string, Texture2D> mNameToTextureMap;
    AnimationCollection mAnimationCollection;
    ResourceManager() = default;
    ~ResourceManager() = default;
    static ResourceManager* mInstance;
};


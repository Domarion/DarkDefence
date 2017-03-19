#pragma once

#include "../GraphicsSystem/newSystem/Texture2D.h"
#include <map>

struct ResourceManager
{
public:
    static ResourceManager* getInstance();
    void loadConfigFromFile(
            const std::string& aFilename,
            std::shared_ptr<RenderingSystem> aRenderingSystem);
    Texture2D getTexture(const std::string& aObjectName) const;

    bool haveTexture(const std::string& aObjectName) const;
private:
    std::map<std::string, Texture2D> mNameToTextureMap;
    ResourceManager() = default;
    ~ResourceManager() = default;
    static ResourceManager* mInstance;
};


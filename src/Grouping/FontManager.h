#pragma once

#include <memory>
#include <map>
#include <string>

#include "../GraphicsSystem/newSystem/Font.h"

class FontManager
{
public:
    static FontManager* getInstance();
    void loadFontList(const std::string& aFilename, std::shared_ptr<RenderingSystem>& aRenderer);
    Font& getFontByKind(const std::string& aFontKind);

private:
    FontManager() = default;
    ~FontManager() = default;
    std::map<std::string, Font > fontList;

    static FontManager* instance_;
};

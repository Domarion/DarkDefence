#pragma once

#include "../GraphicsSystem/newSystem/Font.h"

#include <map>
using std::map;

#include <memory>
using std::shared_ptr;

#include <string>
using std::string;

class FontManager
{
public:
    static FontManager* getInstance();
    void loadFontList(string filename, std::shared_ptr<RenderingSystem> &aRenderer);
    Font& getFontByKind2(string kind);

private:
    FontManager() = default;
    ~FontManager() = default;
    map<string, Font > fontList2;

    static FontManager* instance_;
};

#pragma once

//#include "../GraphicsSystem/CFont.h"
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
//    shared_ptr<CFont>& getFontByKind(string kind);
    Font & getFontByKind2(string kind);

private:
    FontManager();
    ~FontManager();
//    map<string, shared_ptr< CFont > > fontList;
    map<string, Font > fontList2;

    static FontManager* instance_;
};

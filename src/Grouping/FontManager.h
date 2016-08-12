#pragma once

#include "../GraphicsSystem/CFont.h"

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
    void loadFontList(string filename);
    shared_ptr<CFont>& getFontByKind(string kind);

private:
    FontManager();
    ~FontManager();
    map<string, shared_ptr< CFont > > fontList;
    static FontManager* instance_;
};

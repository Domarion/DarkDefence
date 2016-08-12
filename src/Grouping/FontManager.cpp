#include "FontManager.h"
#include "../Utility/textfilefunctions.h"
#include <fstream>
using std::ifstream;
#include <iostream>
#include <sstream>
using std::stringstream;

FontManager* FontManager::instance_ = nullptr;

FontManager::FontManager()
{

}

FontManager *FontManager::getInstance()
{
    if (instance_ == nullptr)
        instance_ = new FontManager();

    return instance_;
}

void FontManager::loadFontList(string filename)
{

    string textString;
    androidText::loadTextFileToString(filename, textString);

    if (!textString.empty())
    {
        stringstream fontConf(textString);

        size_t n = 0;
        fontConf >> n;

        for(size_t i = 0; i < n; ++i)
        {
            string key, fontPath;
            int fontSize;
            int r, g, b;
            fontConf >> key >> fontPath >> fontSize >> r >> g >> b;
            fontList[key] = std::make_shared<CFont>(fontPath, fontSize, r, g, b);
        }
        std::cout << "FontsLoaded:" << std::endl;
    }
    else
        std::cout << "WhatTheFuck in font manager:" << filename << std::endl;


    std::cout << textString << std::endl;
    /*androidText::setRelativePath(filename1);

    ifstream fontConf(filename1);

    if (fontConf.good())
    {
        size_t n = 0;
        fontConf >> n;

        for(size_t i = 0; i < n; ++i)
        {
            string key, fontPath;
            int fontSize;
            int r, g, b;
            fontConf >> key >> fontPath >> fontSize >> r >> g >> b;
            fontList[key] = std::make_shared<CFont>(fontPath, fontSize, r, g, b);
        }
    }
    else
        std::cout << "WhatTheFuck in font manager:" << filename1 << std::endl;
    fontConf.close();*/
}

shared_ptr<CFont>& FontManager::getFontByKind(string kind)
{
    if (fontList.at( kind ).get() == nullptr)
          std::cout << "FontManager::getFontByKind: font null" << std::endl;
    return fontList.at( kind );
}

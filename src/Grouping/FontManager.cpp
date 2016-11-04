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

void FontManager::loadFontList(string filename, std::shared_ptr<RenderingSystem>& aRenderer)
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
//            fontList[key] = std::make_shared<CFont>(fontPath, fontSize, r, g, b);
            fontList2[key]= Font(fontPath,fontSize, r, g, b, aRenderer);
        }
        std::cout << "FontsLoaded:" << std::endl;
    }
    else
        std::cout << "WhatTheFuck in font manager:" << filename << std::endl;


    std::cout << textString << std::endl;

}

//shared_ptr<CFont>& FontManager::getFontByKind(string kind)
//{
//    if (fontList.at( kind ).get() == nullptr)
//          std::cout << "FontManager::getFontByKind: font null" << std::endl;
//    return fontList.at( kind );
//}

Font &FontManager::getFontByKind2(std::string kind)
{
    if (fontList2.at( kind ).getFont() == nullptr)
          std::cout << "FontManager::getFontByKind2: font null" << std::endl;
    return fontList2.at( kind );
}

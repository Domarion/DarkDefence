#include "FontManager.h"
#include "../Utility/textfilefunctions.h"
#include <fstream>
using std::ifstream;

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
    string filename1(filename);
    androidText::setRelativePath(filename1);

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
    fontConf.close();
}

shared_ptr<CFont> FontManager::getFontByKind(string kind)
{
    return fontList[ kind ];
}

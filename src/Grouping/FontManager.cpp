#include <sstream>

#include "FontManager.h"
#include "../Utility/textfilefunctions.h"
#include "Logging/Logger.h"

FontManager* FontManager::instance_ = nullptr;

FontManager* FontManager::getInstance()
{
    if (instance_ == nullptr)
        instance_ = new FontManager();

    return instance_;
}

void FontManager::loadFontList(const std::string& aFilename, std::shared_ptr<RenderingSystem>& aRenderer)
{
    string textString;
    androidText::loadTextFileToString(aFilename, textString);

    if (!textString.empty())
    {
        std::stringstream fontConf(textString);

        size_t n = 0;
        fontConf >> n;

        for(size_t i = 0; i < n; ++i)
        {
            string key, fontPath;
            int fontSize;
            int r, g, b;
            fontConf >> key >> fontPath >> fontSize >> r >> g >> b;
            fontList[key] = Font(fontPath, fontSize, r, g, b, aRenderer);
        }
    }
}

Font& FontManager::getFontByKind(const std::string& aFontKind)
{
    if (fontList.at(aFontKind).getFont() == nullptr)
    {
        LOG_ERROR("Can't Find font by name.");
    }
    return fontList.at( aFontKind );
}

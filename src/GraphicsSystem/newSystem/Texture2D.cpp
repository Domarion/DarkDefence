#include "Texture2D.h"
#include "../../GlobalScripts/Renderer.h"

#include "../../Utility/textfilefunctions.h"

Texture2D::Texture2D()
    :texturePtr(nullptr, SDL_DestroyTexture)
{

}

void Texture2D::setTexture(shared_ptr<SDL_Texture> texture)
{
    texturePtr = texture;

}

void Texture2D::setTextureFromText(const string &ltext, Font lfont)
{
    texturePtr.reset(Renderer::getInstance()->textToTexture(lfont.getFont().get(),ltext, lfont.getFontColor()),
                    SDL_DestroyTexture);
}

shared_ptr<SDL_Texture> Texture2D::getTexture() const
{
    return texturePtr;
}

void Texture2D::loadTexture(const string &filename)
{
    string filename1 = filename;
    androidText::setRelativePath(filename1);
    texturePtr.reset(Renderer::getInstance()->loadTextureFromFile(filename1),
                     SDL_DestroyTexture);

}

void Texture2D::drawAtPosition(Position pos)
{
    SDL_Rect rect = {pos.x, pos.y, getSize().width, getSize().height};
    Renderer::getInstance()->renderTexture(texturePtr.get(), &rect);
}

Size Texture2D::getSize() const
{
    return textureSize;
}

void Texture2D::setSize(Size size)
{
    textureSize = size;
}

void Texture2D::scaleToTexture()
{
    SDL_QueryTexture(getTexture().get(), nullptr, nullptr, &textureSize.width, &textureSize.height);

}

#include "Texture2D.h"
#include "../../Utility/textfilefunctions.h"

Texture2D::Texture2D(std::shared_ptr<RenderingSystem> &renderingContext)
    :texturePtr(nullptr, SDL_DestroyTexture)
    , renderer(renderingContext)
{

}

void Texture2D::setTexture(shared_ptr<SDL_Texture> texture)
{
    texturePtr = texture;

}

void Texture2D::setTextureFromText(const string &ltext, Font lfont)
{
    texturePtr.reset();
    texturePtr = renderer->textToTexture(lfont.getFont().get(),ltext, lfont.getFontColor());
}

const shared_ptr<SDL_Texture>& Texture2D::getTexture() const
{
    return texturePtr;
}

void Texture2D::loadTexture(const string &filename)
{
    string filename1 = filename;
    androidText::setRelativePath(filename1);
    texturePtr.reset();
    texturePtr = renderer->loadTextureFromFile(filename1);
}

void Texture2D::drawAtPosition(Position pos) const
{
    renderer->renderTexture(texturePtr.get(),getSize(),std::move(pos));
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

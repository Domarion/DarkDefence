#include "Texture2D.h"
#include "../../Utility/textfilefunctions.h"

Texture2D::Texture2D(std::shared_ptr<RenderingSystem> &renderingContext)
    :texturePtr(nullptr, SDL_DestroyTexture)
    , renderer(renderingContext)
{

}

Texture2D::Texture2D(const Texture2D &right)
{
    texturePtr = right.texturePtr;
    textureSize = right.textureSize;
    renderer = right.renderer;
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

void Texture2D::loadTexture(const string &filename, bool aRelativePath)
{
    string filename1 = filename;
    if (aRelativePath)
        androidText::setRelativePath(filename1);
    texturePtr.reset();
    texturePtr = renderer->loadTextureFromFile(filename1);
}

void Texture2D::drawAtPosition(Position pos) const
{
    renderer->renderTexture(texturePtr.get(), getSize(), pos);
}

void Texture2D::drawPartAtPosition(Position pos, const SDL_Rect *clip) const
{
    renderer->renderTexture(texturePtr.get(), pos, clip);
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

bool Texture2D::hasTexture() const
{
    return texturePtr != nullptr;
}

void Texture2D::resetTexture()
{
    texturePtr.reset();
}

void Texture2D::setAsRenderTarget()
{
    renderer->renderToTarget(getTexture().get());
}

void Texture2D::unSetAsRenderTarget()
{
    renderer->renderToTarget(nullptr);
}

void Texture2D::createBlankTexture(SDL_TextureAccess aAccess)
{
    texturePtr = std::move(renderer->createBlankTexture(getSize(), aAccess));
}

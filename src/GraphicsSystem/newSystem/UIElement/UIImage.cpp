#include "UIImage.h"

UIImage::UIImage(std::shared_ptr<RenderingSystem>& aRenderingContext)
    : Leaf(aRenderingContext)
    , mTexture(aRenderingContext)
{
}

void UIImage::loadTexture(const std::string& aFilename)
{
    mTexture.loadTexture(aFilename);
}

void UIImage::setTexture(const Texture2D& aTexture)
{
    mTexture = aTexture;
}

void UIImage::draw() const
{
    mTexture.drawAtPosition(this->getPosition());
}

Size UIImage::getSize() const
{
    return mTexture.getSize();
}

void UIImage::setSize(Size aSize)
{
    mTexture.setSize(aSize);
}

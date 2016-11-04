#include "UIImage.h"

UIImage::UIImage(std::shared_ptr<RenderingSystem> &aRenderingContext)
    :Leaf(aRenderingContext)
    , mTexture(aRenderingContext)
{

}

void UIImage::loadTexture(const std::string &filename)
{
    mTexture.loadTexture(filename);
}

void UIImage::draw() const
{
    mTexture.drawAtPosition(this->getPosition());
}

Size UIImage::getSize() const
{
    return mTexture.getSize();
}

void UIImage::setSize(Size size)
{
    mTexture.setSize(size);
}

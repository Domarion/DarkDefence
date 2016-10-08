#include "UIProgressBar.h"


UIProgressBar::UIProgressBar(std::shared_ptr<RenderingSystem> &aRenderingContext, const Texture2D &background, const Texture2D &foreground)
    :Leaf(aRenderingContext), backTexture(background), frontTexture(foreground)
{

}

void UIProgressBar::calculateProgress(int current, int max)
{
    if (max > 0)
    {
       Size frontSize = frontTexture.getSize();
       frontSize.width = static_cast<int>(backTexture.getSize().width *(current + 0.0)/max);
       frontTexture.setSize(frontSize);
    }
}

void UIProgressBar::draw() const
{
    backTexture.drawAtPosition(getPosition());
    frontTexture.drawAtPosition(getPosition());
}

Size UIProgressBar::getSize() const
{
    backTexture.getSize();
}

void UIProgressBar::setSize(Size size)
{
    backTexture.setSize(size);
    frontTexture.setSize(size);
}

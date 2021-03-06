#include "UISlot.h"

UISlot::UISlot(const std::string& aBackImagePath, std::shared_ptr<RenderingSystem>& aRenderer)
    : Leaf(aRenderer)
    , backGround(aRenderer)
    , foreGround(aRenderer)
{
    backGround.loadTexture(aBackImagePath);
}

void UISlot::loadForeground(const std::string& aPath)
{
    foreGround.loadTexture(aPath);
}

void UISlot::setForeground(Texture2D& aTexture)
{
    foreGround = aTexture;
    foreGround.setSize(backGround.getSize());
}

void UISlot::resetForeground()
{
    foreGround.resetTexture();
}

void UISlot::draw() const
{
    backGround.drawAtPosition(getPosition());
    if (foreGround.hasTexture())
    {
        foreGround.drawAtPosition(getPosition());
    }
}

Size UISlot::getSize() const
{
    return backGround.getSize();
}

void UISlot::setSize(Size aSize)
{
    backGround.setSize(aSize);
    foreGround.setSize(aSize);
}

#include "CompositeLabel.h"

CompositeLabel::CompositeLabel()
{

}

CTexture CompositeLabel::getIcon() const
{
    return icon;
}

void CompositeLabel::setIcon(const CTexture &value)
{
    icon = value;
}

void CompositeLabel::draw()
{
    icon.draw();
    CTexture::draw();
}

SDL_Rect CompositeLabel::getIconRect() const
{
    return icon.getRect();
}

void CompositeLabel::setIconRect(const SDL_Rect &value)
{
    icon.setRect(value);
}

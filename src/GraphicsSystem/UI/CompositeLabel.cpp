#include "CompositeLabel.h"

CompositeLabel::CompositeLabel()
{

}

CompositeLabel::~CompositeLabel()
{

}

void CompositeLabel::loadIcon(const string &filename)
{
    icon.loadTexture(filename);
}

SDL_Texture * CompositeLabel::getIcon() const
{
    return icon.getTexture();
}

void CompositeLabel::setIcon(SDL_Texture * const value)
{
    icon.setTexture(value);
}



void CompositeLabel::draw()
{
    icon.draw();
    Label::draw();
}

void CompositeLabel::setPos(int x, int y)
{
    setPosX(x);
    setPosY(y);
}




void CompositeLabel::setPosX(int x)
{
     icon.setPosX(x);
     Label::setPosX(x + icon.getRect().w);
}

void CompositeLabel::setPosY(int y)
{
    icon.setPosY(y);
    Label::setPosY(y);
}

SDL_Rect CompositeLabel::getIconRect() const
{
    return icon.getRect();
}

const SDL_Rect &CompositeLabel::getRect() const
{

    return Label::getRect();//TODO::fix rect
}

void CompositeLabel::setIconRect(const SDL_Rect &value)
{
    icon.setRect(value);
}

void CompositeLabel::setIconRect(int x, int y, int w, int h)
{
    icon.setRect(x, y, w, h);
}

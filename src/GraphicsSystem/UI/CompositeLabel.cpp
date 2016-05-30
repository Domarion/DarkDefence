#include "CompositeLabel.h"

CompositeLabel::CompositeLabel()
   // :fullRect({0,0,0,0})
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

    //fullRect.x = x;
     icon.setPosX(x);
     Label::setPosX(x + icon.getRect().w);
}

void CompositeLabel::setPosY(int y)
{
    //fullRect.y = y;
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
   // fullRect.x = value.x;
    //fullRect.y = value.y;
    //fullRect.w = Label::getRect().w + value.w;
    //fullRect.h = value.h;
    icon.setRect(value);
}

void CompositeLabel::setIconRect(int x, int y, int w, int h)
{
    icon.setRect(x, y, w, h);
}

/*void CompositeLabel::setRect(const SDL_Rect &rect)
{
    fullRect = rect;
    icon.setPosX(fullRect.x);
    icon.setPosY(fullRect.y);
    Label::setPosX(fullRect.x + icon.getRect().w);
    Label::setPosY(fullRect.y);
}*/

/*void CompositeLabel::setRect(int x, int y, int w, int h)
{
    SDL_Rect tmp = {x,y,w,h};
    setRect(tmp);
}*/

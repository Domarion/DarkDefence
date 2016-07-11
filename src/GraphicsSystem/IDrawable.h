#pragma once
#include <SDL_rect.h>
#include <SDL_render.h>

class IDrawable//TODO: Переработать интерфейс
{
public:
    virtual void draw() = 0;
    virtual void setTexture(SDL_Texture* value) = 0;
    virtual SDL_Texture* getTexture() const = 0;
    virtual const SDL_Rect& getRect() const = 0;
    virtual void setRect(const SDL_Rect& rect) = 0;
    virtual void setRect(int x, int y, int w, int h) = 0;
    virtual void setPos(int x, int y) = 0;
    virtual void setPosX(int x)= 0;
    virtual void setPosY(int y)= 0;
    virtual void setSize(int w, int h) = 0;
    virtual ~IDrawable(){}
    virtual int getDrawOrder(){return 0;}// реализовать во всех классах, поддерживающих интерфейс
};

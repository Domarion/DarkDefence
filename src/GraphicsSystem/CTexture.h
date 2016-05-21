
#pragma once
#include <SDL.h>
//#include <string>
#include "../GlobalScripts/Renderer.h"
class CTexture
{
public:

    CTexture(SDL_Texture* aTexture, const SDL_Rect& newRect);
    CTexture(SDL_Texture* aTexture = nullptr);
	virtual void draw();
	virtual ~CTexture();
    virtual SDL_Texture* getTexture() const;
    void setTextureFromSurface(SDL_Surface* surface);
    void setTexture(SDL_Texture*  value);
    virtual void setRect(int x, int y, int w, int h);
    virtual void setRect(const SDL_Rect& value);
    virtual const SDL_Rect& getRect() const;
    virtual void setPosX(int x);
    virtual void setPosY(int y);
    virtual void setPos(int x, int y);
protected:



private:
	SDL_Texture* texture;
    SDL_Rect rect;
};

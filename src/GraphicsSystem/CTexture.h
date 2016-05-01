
#pragma once
#include <SDL2/SDL.h>
//#include <string>
#include "../GlobalScripts/Renderer.h"
class CTexture
{
public:

    CTexture(SDL_Texture* aTexture, const SDL_Rect& newRect);
    CTexture(SDL_Texture* aTexture = nullptr);
	virtual void draw();
	virtual ~CTexture();
    virtual SDL_Texture* const getTexture() const;
    void setTextureFromSurface(SDL_Surface* surface);
    void setTexture(SDL_Texture* const value);
    virtual void setRect(int x, int y, int w, int h);
    virtual void setRect(const SDL_Rect& value);
    const SDL_Rect& getRect() const;
    void setPosX(int x);
    void setPosY(int y);
    void setPos(int x, int y);
protected:

private:
	SDL_Texture* texture;
    SDL_Rect rect;
};

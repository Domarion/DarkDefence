
#pragma once

#include <SDL.h>
#include "IDrawable.h"
#include "CFont.h"

class CTexture: public IDrawable

{
public:

    CTexture(SDL_Texture* aTexture, const SDL_Rect& newRect);
    CTexture(SDL_Texture* aTexture = nullptr);
    CTexture(const string& filename);

    virtual ~CTexture();
    void free();
    virtual void draw() override;


    void setTextureFromSurface(SDL_Surface* surface);

    void setTextureFromText(const string& text, const CFont& font);
    void loadTexture(const string& filename);


    virtual SDL_Texture* getTexture() const override;
    virtual void setTexture(SDL_Texture*  value) override;

    virtual void setPosX(int x) override;
    virtual void setPosY(int y) override;
    virtual void setRect(int x, int y, int w, int h) override;
    virtual void setRect(const SDL_Rect& value) override;
    virtual const SDL_Rect& getRect() const override;

    virtual void setPos(int x, int y) override;

private:
    void autoScale();
	SDL_Texture* texture;
    SDL_Rect rect;
};

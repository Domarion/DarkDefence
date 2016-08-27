
#pragma once

#include <SDL.h>
#include "IDrawable.h"
#include "CFont.h"
#include <memory>

class CTexture: public IDrawable
{
public:

    CTexture(SDL_Texture* aTexture, const SDL_Rect& newRect);
    explicit CTexture(SDL_Texture* aTexture = nullptr);
    explicit CTexture(const string& filename);
    explicit CTexture(int aWidth, int aHeight);
    virtual ~CTexture();
    void free();
    virtual void draw() override;
    virtual void drawPart(SDL_Rect*  clip);

    void setTextureFromSurface(SDL_Surface* surface);

    void setTextureFromText(string& text, std::shared_ptr<CFont> font);
    void loadTexture(const string& filename);

    int getZOrder() const;
    void setZOrder(int value);

    // IDrawable interface
public:
    virtual void setSize(int w, int h) override;
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
    int zOrder;


};

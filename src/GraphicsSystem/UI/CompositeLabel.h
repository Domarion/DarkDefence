#pragma once
#include "Label.h"


class CompositeLabel: public Label
{
public:
    CompositeLabel();
    virtual ~CompositeLabel();


    SDL_Texture* getIcon() const;
    void setIcon(SDL_Texture* const value);
    void loadIcon(const string& filename);
    virtual void draw() override;

    virtual void setPos(int x, int y) override;
    virtual void setPosX(int x);
    virtual void setPosY(int y);
    SDL_Rect getIconRect() const;
    virtual const SDL_Rect& getRect() const override;
    void setIconRect(const SDL_Rect &value);
    void setIconRect(int x, int y, int w, int h);

private:
    CTexture icon;

};


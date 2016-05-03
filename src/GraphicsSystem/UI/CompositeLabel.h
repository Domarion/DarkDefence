#pragma once
#include "Label.h"
#include "GroupBox.h"

class CompositeLabel: public Label
{
public:
    CompositeLabel();
    virtual ~CompositeLabel();

    CTexture getIcon() const;
    void setIcon(const CTexture &value);
    virtual void draw() override;

    SDL_Rect getIconRect() const;
    void setIconRect(const SDL_Rect &value);

private:
    CTexture icon;

};


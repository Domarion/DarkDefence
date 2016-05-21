#pragma once
#include "CTexture.h"
#include "UI/Label.h"
class ShopItemUI: public CTexture
{
public:
    ShopItemUI();
    virtual ~ShopItemUI();
    // CTexture interface
public:

    void init(CFont& font,
              string iconPath, string aCaption,
              string aDescription, string aPrice = "none");
    virtual void draw() override;
    virtual void setRect(int x, int y, int w, int h) override;
    virtual void setPosX(int x) override;
    virtual void setPosY(int y) override;
    virtual void setPos(int x, int y) override;
private:
    CTexture icon;
    Label caption;
    Label description;
    Label price;
    Label buyButton;
};


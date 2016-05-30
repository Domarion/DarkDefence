#include "ShopItemUI.h"

ShopItemUI::ShopItemUI()
    :CTexture()
{
   /*CTexture icon;
    Label caption;
    Label description;
    Label buyButton;
    */

}

ShopItemUI::~ShopItemUI()
{
    icon.free();
    caption.free();
    description.free();
    price.free();
    buyButton.free();
}

void ShopItemUI::init(std::shared_ptr<CFont> font, string iconPath, string aCaption, string aDescription, string aPrice)
{

    icon.loadTexture(iconPath);
    int x = getRect().x;
    int y = getRect().y;
    icon.setRect(x, y, 48, 48);

    caption.setFont(font);
    caption.setText(aCaption);
    caption.setPos(x + icon.getRect().w, y);

    description.setFont(font);
    description.setText(aDescription);
    description.setPos(x + icon.getRect().w, y + caption.getRect().h);

    price.setFont(font);
    price.setText(aPrice);
    price.setPos(x + icon.getRect().w, description.getRect().y + description.getRect().h);
    string buyString = "Купить";

    buyButton.setFont(font);
    buyButton.setText(buyString);
    buyButton.setPos(price.getRect().x + price.getRect().w, description.getRect().y + description.getRect().h);

    if (aPrice == "none")
    {
        price.setRect(0,0,0,0);
        buyButton.setRect(0,0,0,0);
         CTexture::setRect(x, y,icon.getRect().w + description.getRect().w, icon.getRect().h);
    }
    else
    {


        CTexture::setRect(x, y,icon.getRect().w + description.getRect().w, icon.getRect().h + buyButton.getRect().h );
    }
}

void ShopItemUI::draw()
{

    CTexture::draw();

    icon.draw();
    caption.draw();
    description.draw();
    if (price.getText() != "none")
    {
        price.draw();
        buyButton.draw();
    }
}

void ShopItemUI::setRect(int x, int y, int w, int h)
{
    CTexture::setRect(x, y, w, h);

    icon.setPos(x, y);
    caption.setPos(x + icon.getRect().w, y);
    description.setPos(x + icon.getRect().w, y + caption.getRect().h);

    if (price.getText() != "none")
    {
        price.setPos(x + icon.getRect().w, description.getRect().y + description.getRect().h);
        buyButton.setPos(price.getRect().x + price.getRect().w, description.getRect().y + description.getRect().h);
    }
}


void ShopItemUI::setPosX(int x)
{
    CTexture::setPosX(x);
    icon.setPosX(x);
    caption.setPosX(x + icon.getRect().w);
    description.setPosX(x + icon.getRect().w);

    if (price.getText() != "none")
    {
        price.setPosX(x + icon.getRect().w);
        buyButton.setPosX(price.getRect().x + price.getRect().w);
    }
}

void ShopItemUI::setPosY(int y)
{
    CTexture::setPosY(y);
    icon.setPosY(y);
    caption.setPosY( y);
    description.setPosY(y + caption.getRect().h);
    if (price.getText() != "none")
    {
        price.setPosY(description.getRect().y + description.getRect().h);
        buyButton.setPosY(description.getRect().y + description.getRect().h);
    }
}


void ShopItemUI::setPos(int x, int y)
{
    setPosX(x);
    setPosY(y);
}

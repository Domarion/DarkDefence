#include "UILabel.h"

UILabel::UILabel(const string &ltext, const Font &lfont)
    :text(ltext), font(lfont)
{
    setText(ltext);

}

void UILabel::setText(const string &ltext)
{
    text = ltext;
    textTexture.setTextureFromText(text, font);
    textTexture.scaleToTexture();
}

void UILabel::draw()
{
    textTexture.drawAtPosition(getPosition());
}

Size UILabel::getSize() const
{
    textTexture.getSize();
}

void UILabel::setSize(Size size)
{
    textTexture.setSize(size);
}

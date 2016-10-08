#include "UILabel.h"

UILabel::UILabel(const string &ltext, const Font &lfont, std::shared_ptr<RenderingSystem> &aRenderingContext)
    : Leaf(aRenderingContext)
    , text(ltext)
    , font(lfont)
    , textTexture(aRenderingContext)

{
    setText(ltext);

}

void UILabel::setText(const string &ltext)
{
    text = ltext;
    textTexture.setTextureFromText(text, font);
    textTexture.scaleToTexture();
}

void UILabel::draw() const
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

#include "UILabel.h"

UILabel::UILabel(const string& aText, const Font& aFont, std::shared_ptr<RenderingSystem>& aRenderingContext)
    : Leaf(aRenderingContext)
    , text(aText)
    , font(aFont)
    , textTexture(aRenderingContext)
{
    setText(aText);
}

void UILabel::setText(const string& aText)
{
    text = aText;
    textTexture.setTextureFromText(text, font);
    textTexture.scaleToTexture();
}

void UILabel::draw() const
{
    textTexture.drawAtPosition(getPosition());
}

Size UILabel::getSize() const
{
    return textTexture.getSize();
}

void UILabel::setSize(Size size)
{
    textTexture.setSize(size);
}

#pragma once

#include "../Leaf.h"
#include "../Texture2D.h"
#include "../Font.h"

class UILabel : public Leaf
{
public:
    UILabel() = default;
    explicit UILabel(const string& aText, const Font& aFont, std::shared_ptr<RenderingSystem>& aRenderingContext);

    virtual ~UILabel() = default;

    void setText(const string& aText);

    // IComposite interface
    virtual void draw() const override;
    virtual Size getSize() const override;
    virtual void setSize(Size size) override;

private:
    string text;
    Font font;
    Texture2D textTexture;
};


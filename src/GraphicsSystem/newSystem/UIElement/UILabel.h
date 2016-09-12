#pragma once

#include "../Leaf.h"
#include "../Texture2D.h"
#include "../Font.h"


class UILabel final: public Leaf
{
public:
    UILabel() = default;
    explicit UILabel(const string& ltext, const Font& lfont);
    virtual ~UILabel() = default;

    void setText(const string& ltext);
    // IComposite interface
    virtual void draw() override;
    virtual Size getSize() const override;
    virtual void setSize(Size size) override;

private:
    string text;
    Font font;
    Texture2D textTexture;
};


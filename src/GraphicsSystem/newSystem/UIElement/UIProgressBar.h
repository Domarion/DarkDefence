#pragma once
#include "../Leaf.h"
#include "../Texture2D.h"

class UIProgressBar final: public Leaf
{
public:
    UIProgressBar() = default;
    explicit UIProgressBar(const Texture2D& background, const Texture2D& foreground);
    virtual ~UIProgressBar() = default;
    void calculateProgress(int current, int max);

    // IComposite interface
    virtual void draw() override;
    virtual Size getSize() const override;
    virtual void setSize(Size size) override;

private:
    Texture2D backTexture;
    Texture2D frontTexture;
};
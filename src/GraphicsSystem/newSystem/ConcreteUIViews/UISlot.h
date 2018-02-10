#pragma once

#include "../Leaf.h"
#include "../Texture2D.h"

class UISlot final: public Leaf
{
public:
    UISlot(const std::string& aBackImagePath, std::shared_ptr<RenderingSystem>& aRenderer);
    void loadForeground(const std::string& aPath);
    void setForeground(Texture2D& aTexture);
    void resetForeground();
private:
    Texture2D backGround;
    Texture2D foreGround;

    // IComposite interface
public:
    void draw() const override;
    Size getSize() const override;
    void setSize(Size aSize) override;
};

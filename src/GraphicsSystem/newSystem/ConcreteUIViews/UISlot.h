#pragma once
#include "../Leaf.h"
#include "../Texture2D.h"

class UISlot: public Leaf
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
    virtual void draw() const override;
    virtual Size getSize() const override;
    virtual void setSize(Size size) override;
};

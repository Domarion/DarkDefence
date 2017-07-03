#pragma once

#include "../Leaf.h"
#include "../Texture2D.h"
class UIImage: public Leaf
{
public:
    explicit UIImage(std::shared_ptr<RenderingSystem>& aRenderingContext);

    UIImage() = delete;
    virtual ~UIImage() = default;
    void loadTexture(const string& filename);
    void setTexture(const Texture2D& aTexture);


    // IComposite interface
public:
    virtual void draw() const override;
    virtual Size getSize() const override;
    virtual void setSize(Size size) override;
private:
    Texture2D mTexture;
};

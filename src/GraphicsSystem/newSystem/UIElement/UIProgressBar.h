#pragma once

#include <functional>

#include "../Leaf.h"
#include "../Texture2D.h"
#include "../../../Input/InputHandler.h"

class UIProgressBar final: public Leaf,  public InputHandler
{
public:
    UIProgressBar() = default;
    explicit UIProgressBar(
            std::shared_ptr<RenderingSystem>& aRenderingContext,
            const Texture2D& background,
            const Texture2D& foreground,
            bool aIsVertical = false);
    virtual ~UIProgressBar() = default;
    void calculateProgress(int current, int max);
    void ConnectMethod(std::function<void (std::string)> method);

    // InputHandler interface
    virtual bool onClick(Position point) override;

    // IComposite interface
    virtual void draw() const override;
    virtual Size getSize() const override;
    virtual void setSize(Size size) override;

private:

    inline int getMeasurementPart(int aValue, double aCoeff) const;

    Texture2D backTexture;
    Texture2D frontTexture;
    bool isVertical = false;

    Size backSize;
    Size frontSize;
    Position backDrawPosition;
    Position frontDrawPosition;
    SDL_Rect backRect;
    SDL_Rect frontRect;

    std::function<void(std::string)> connectedMethod;
};

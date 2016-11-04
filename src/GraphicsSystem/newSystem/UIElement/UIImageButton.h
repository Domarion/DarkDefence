#pragma once
#include <functional>
#include "UIImage.h"
#include "../../../Input/InputHandler.h"

class UIImageButton final: public UIImage,  public InputHandler
{
public:
    explicit UIImageButton(std::shared_ptr<RenderingSystem>& aRenderingContext);

    UIImageButton() = delete;
    virtual ~UIImageButton() = default;

    void ConnectMethod(std::function<void(std::string)> method);

    // InputHandler interface
public:
    virtual bool onClick(SDL_Point *point) override;

private:
    std::function<void(std::string)> connectedMethod;

};

#pragma once

#include <functional>

#include "UIImage.h"
#include "../../../Input/InputHandler.h"

class UIImageButton final: public UIImage, public InputHandler
{
public:
    explicit UIImageButton(std::shared_ptr<RenderingSystem>& aRenderingContext);
    virtual ~UIImageButton() = default;

    void ConnectMethod(std::function<void(std::string)> method);

    void SetCanConsumeInput(bool aShouldConsume);
    // InputHandler interface
public:
    virtual bool onClick(Position point) override;
    virtual bool canConsumeInput() const override;

private:
    std::function<void(std::string)> connectedMethod;
    bool mShouldConsumeInput = false;
};

#pragma once

#include <functional>

#include "UILabel.h"
#include "../../../Input/InputHandler.h"

class UITextButton final: public UILabel,  public InputHandler
{
public:
    explicit UITextButton(
        const string& ltext, const Font& lfont, std::shared_ptr<RenderingSystem>& aRenderingContext);

    UITextButton() = delete;
    virtual ~UITextButton() = default;

    void setMessage(const std::string& aMsg);
    void ConnectMethod(std::function<void(std::string)> method);

    // InputHandler interface
    virtual bool onClick(Position point) override;

private:
    std::function<void(std::string)> connectedMethod;
    std::string msg;
};

#pragma once
#include <functional>
#include "UILabel.h"
#include "../../../Input/InputHandler.h"

class UITextButton final: public UILabel,  public InputHandler
{
public:
    explicit UITextButton(const string& ltext, const Font& lfont,
                          std::shared_ptr<RenderingSystem>& aRenderingContext);

    UITextButton() = delete;
    virtual ~UITextButton() = default;

    void ConnectMethod(std::function<void(std::string)> method);

    // InputHandler interface
public:
    virtual bool onClick(SDL_Point *point) override;

private:
    std::function<void(std::string)> connectedMethod;

};

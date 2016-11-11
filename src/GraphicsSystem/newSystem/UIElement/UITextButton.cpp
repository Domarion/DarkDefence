#include "UITextButton.h"
#include <iostream>
UITextButton::UITextButton(const std::string &ltext, const Font &lfont, std::shared_ptr<RenderingSystem> &aRenderingContext)
    :UILabel(ltext, lfont, aRenderingContext)
{

}

void UITextButton::ConnectMethod(std::function<void (std::string)> method)
{
    connectedMethod = method;

}


bool UITextButton::onClick(Position point)
{
    SDL_Rect rect = SDL_Rect();
    rect.x = getPosition().x;
    rect.y = getPosition().y;
    rect.w = getSize().width;
    rect.h = getSize().height;

    SDL_Point sPoint{point.x, point.y};

    bool result = SDL_PointInRect(&sPoint, &rect);

    std::cout << "ClickingResult" << std::boolalpha << result;
    if (result && connectedMethod != nullptr)
        connectedMethod("zero");

    return result;
}

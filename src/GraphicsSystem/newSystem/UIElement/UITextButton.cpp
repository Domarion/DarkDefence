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

SDL_Rect *UITextButton::getRect()
{
    SDL_Rect* rect = new SDL_Rect();
    rect->x = getPosition().x;
    rect->y = getPosition().y;
    rect->w = getSize().width;
    rect->h = getSize().height;
    return rect;
}

bool UITextButton::onClick(SDL_Point *point)
{

    bool result = SDL_PointInRect(point, getRect());

    std::cout << "ClickingResult" << std::boolalpha << result;
    if (result)
        connectedMethod("zero");

    return result;
}

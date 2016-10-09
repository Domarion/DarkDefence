#include "UIImageButton.h"

UIImageButton::UIImageButton(std::shared_ptr<RenderingSystem> &aRenderingContext)
    :UIImage(aRenderingContext)
{

}

void UIImageButton::ConnectMethod(std::function<void (std::string)> method)
{
    connectedMethod = method;
}

SDL_Rect *UIImageButton::getRect()
{
    SDL_Rect* rect = new SDL_Rect();
    rect->x = getPosition().x;
    rect->y = getPosition().y;
    rect->w = getSize().width;
    rect->h = getSize().height;
    return rect;
}

bool UIImageButton::onClick(SDL_Point *point)
{
    bool result = SDL_PointInRect(point, getRect());

    std::cout << "ClickingResult" << std::boolalpha << result;
    if (result)
        connectedMethod("zero");

    return result;
}

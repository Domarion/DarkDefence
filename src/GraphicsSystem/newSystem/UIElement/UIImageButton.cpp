#include "UIImageButton.h"

UIImageButton::UIImageButton(std::shared_ptr<RenderingSystem> &aRenderingContext)
    :UIImage(aRenderingContext)
{

}

void UIImageButton::ConnectMethod(std::function<void (std::string)> method)
{
    connectedMethod = method;
}

bool UIImageButton::onClick(Position point)
{
    SDL_Rect rect = SDL_Rect();
    rect.x = getPosition().x;
    rect.y = getPosition().y;
    rect.w = getSize().width;
    rect.h = getSize().height;

    SDL_Point sPoint{point.x, point.y};

    bool result = SDL_PointInRect(&sPoint, &rect);

    std::cout << "ClickingResult" << std::boolalpha << result;
    if (result)
        connectedMethod("zero");

    return result;
}

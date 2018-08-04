#include "UIImageButton.h"

UIImageButton::UIImageButton(std::shared_ptr<RenderingSystem>& aRenderingContext)
    : UIImage(aRenderingContext)
{
}

void UIImageButton::ConnectMethod(std::function<void (std::string)> method)
{
    connectedMethod = method;
}

void UIImageButton::SetCanConsumeInput(bool aShouldConsume)
{
    mShouldConsumeInput = aShouldConsume;
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

    if (result && connectedMethod)
    {
        connectedMethod("zero");
    }

    return result;
}

bool UIImageButton::canConsumeInput() const
{
    return mShouldConsumeInput;
}

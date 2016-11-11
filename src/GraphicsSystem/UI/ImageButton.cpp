#include "ImageButton.h"

ImageButton::ImageButton()
    :CTexture()
{

}

ImageButton::~ImageButton()
{

}

bool ImageButton::onClick(Position point)
{
    SDL_Point sPoint{point.x, point.y};
    bool result = SDL_PointInRect(&sPoint, &getRect());

    if (result && connectedMethod != nullptr)
    {
      //  std::cout << "Clicked" << std::endl;
        connectedMethod("zero");
        //TODO: something similar to delegate
    }
    return result;
}

void ImageButton::ConnectMethod(std::function<void (string)> method)
{
    connectedMethod = method;
}

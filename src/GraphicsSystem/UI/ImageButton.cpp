#include "ImageButton.h"

ImageButton::ImageButton()
    :CTexture()
{

}

ImageButton::~ImageButton()
{

}

bool ImageButton::onClick(SDL_Point *point)
{
    bool result = SDL_PointInRect(point, &getRect());

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

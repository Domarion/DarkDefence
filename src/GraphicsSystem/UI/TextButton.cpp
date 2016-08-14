/*
 * TextButton.cpp
 *
 *  Created on: 18 марта 2016 г.
 *      Author: kostya_hm
 */

#include "TextButton.h"
#include <iostream>
TextButton::TextButton()
:Label()
{

}

TextButton::~TextButton()
{

}


bool TextButton::onClick(SDL_Point* point)
{


    bool result = SDL_PointInRect(point, &getRect());

    if (result)
        connectedMethod("zero");

    return result;
}

void TextButton::ConnectMethod(std::function<void(std::string)> method)
{
    connectedMethod = method;
}

/*
 * TextButton.cpp
 *
 *  Created on: 18 марта 2016 г.
 *      Author: kostya_hm
 */

#include "TextButton.h"
//#include <iostream>
TextButton::TextButton()
:Label()
{
	// TODO Auto-generated constructor stub

}

TextButton::~TextButton()
{
	// TODO Auto-generated destructor stub

}


bool TextButton::onClick(SDL_Point* point)
{


    bool result = SDL_PointInRect(point, &getRect());

	if (result)
	{
        //std::cout << "Clicked" << std::endl;
		connectedMethod("zero");
		//TODO: something similar to delegate
	}
	return result;
}

void TextButton::ConnectMethod(std::function<void(std::string)> method)
{
	connectedMethod = method;
}

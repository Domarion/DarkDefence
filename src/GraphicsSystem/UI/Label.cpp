/*
 * Label.cpp
 *
 *  Created on: 13 марта 2016 г.
 *      Author: kostya_hm
 */

#include "Label.h"
#include <iostream>
using std::cout;
using std::endl;


Label::Label(SDL_Renderer *rptr, const string& lText)
:CTexture(rptr, nullptr, nullptr),lFont(nullptr)
{
	// TODO Auto-generated constructor stub
	setText(lText);

}
Label::Label()
:lFont(nullptr)
{
	setText("");
}

Label::~Label()
{



	if (lFont != nullptr)
		TTF_CloseFont(lFont);


	// TODO Auto-generated destructor stub
}

string Label::getText() const
{
	return text;
}

void Label::setText(const string& value)
{
	text = value;
	convertTextToTexture();
}


const TTF_Font& Label::getTTFFont() const
{
	return *lFont;//TODO:: nullptr dereference possible...
}

void Label::setTTFFont(TTF_Font* value)
{
	//if (lFont == nullptr)
	//	lFont = new TTF_Font();
	lFont = value;
}

void Label::loadFont(string path, int size)
{
	lFont = TTF_OpenFont(path.c_str(), size);
	if(lFont == nullptr)
	{
		cout << "Can't load Font: " << SDL_GetError() << endl;
	}
}


void Label::convertTextToTexture()
{
	if (lFont != nullptr && hasRenderer())
	{
        SDL_Color color = {255, 255, 255};

		SDL_Surface* tempSurface = TTF_RenderUTF8_Solid(lFont, text.c_str(), color);

		setTextureFromSurface(tempSurface);

		SDL_FreeSurface(tempSurface);
	}
}

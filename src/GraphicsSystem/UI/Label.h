/*
 * Label.h
 *
 *  Created on: 13 марта 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include "../CTexture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
using std::string;

class Label: public CTexture
{
public:
	Label(SDL_Renderer *rptr, const string& lText);
	Label();
	~Label();
	void loadFont(string path, int size);
	string getText() const;
	void setText(const string& value);
	const TTF_Font& getTTFFont() const;
	void setTTFFont(TTF_Font* value);


private:
	void convertTextToTexture();
	string text;
	TTF_Font* lFont;

};


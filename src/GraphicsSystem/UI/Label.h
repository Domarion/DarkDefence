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
    Label(const string& lText);
	Label();
	~Label();

    //void loadFont(string path, int size);
	string getText() const;
    void setText(const string& value);
	const TTF_Font& getTTFFont() const;
	void setTTFFont(TTF_Font* value);
    void setFont(TTF_Font* value, int r, int g, int b);
    void setFontColor(int r, int g, int b);
    void setFont(TTF_Font *value, SDL_Color& color);
    void setFontColor(SDL_Color& color);
    void autoScale();
    SDL_Color& getFontColor();

private:
	void convertTextToTexture();
	string text;
	TTF_Font* lFont;
    SDL_Color fontColor;

};

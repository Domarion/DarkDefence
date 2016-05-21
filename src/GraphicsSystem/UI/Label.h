/*
 * Label.h
 *
 *  Created on: 13 марта 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include "../CTexture.h"


class Label: public IDrawable
{
public:
    Label(const string& lText, const CFont& lFont);
    Label(const string& lText);
	Label();
	~Label();

    // IDrawable interface
public:
    virtual void draw() override;
    virtual const SDL_Rect &getRect() const override;
    virtual void setRect(const SDL_Rect &rect) override;
    virtual void setRect(int x, int y, int w, int h) override;
    virtual void setPos(int x, int y) override;
    virtual void setTexture(SDL_Texture *value) override;

    virtual SDL_Texture* getTexture() const override;

public:
    virtual void loadTexture(const string& filename);
	string getText() const;
    void setText(const string& value);
    void setFont(const CFont& value);


private:
    string text;
    CFont font;
    CTexture texture;


    // IDrawable interface
public:
    virtual void setPosX(int x) override;
    virtual void setPosY(int y) override;
};

/*
 * ProgressBar.h
 *
 *  Created on: 21 марта 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include "../CTexture.h"


class ProgressBar: public CTexture
{
public:
	ProgressBar();
	virtual ~ProgressBar();
    const SDL_Rect& getFrontRect() const;
	SDL_Texture* getFrontTexture() const;
	void setFrontTexture(SDL_Texture* frontTexture);
	virtual void draw() override;
    virtual void setRect(const SDL_Rect& value) override;
    virtual void setRect(int x, int y, int w, int h) override;
	void calculateFront(int current, int max);

private:
    void setFrontRect(const SDL_Rect& value);
    void setFrontRect(int x, int y, int w, int h);
    //SDL_Rect frontRect;
    CTexture frontTexture;


    // CTexture interface
public:
    virtual void setPosX(int x);
    virtual void setPosY(int y);
    virtual void setPos(int x, int y);
};


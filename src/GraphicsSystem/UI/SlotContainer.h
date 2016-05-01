/*
 * SlotContainer.h
 *
 *  Created on: 28 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once

#include <vector>
#include "../../Input/InputHandler.h"
#include <functional>
using std::vector;
#include "../CTexture.h"
class SlotContainer: public CTexture, public InputHandler
{
public:
	SlotContainer(int slotsCount);
	virtual ~SlotContainer();
	void addItem(CTexture* item, int index);
	void removeItem(int index);
	virtual void draw() override;
	virtual bool onClick(SDL_Point* point) override;
	virtual void ConnectMethod(std::function<bool(int)> method);
	virtual bool containsPoint(int x, int y) const override;
	void setItemRect(int index, SDL_Rect* rect);
private:
	vector<CTexture*> slots;
	int itemWidth, itemHeight;
protected:
	std::function<bool(int)> connectedMethod;
};


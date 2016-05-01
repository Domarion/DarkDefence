/*
 * ScrollList.h
 *
 *  Created on: 19 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include <functional>
#include "../CTexture.h"
#include <vector>
using std::vector;
#include "../../Input/InputHandler.h"
class ScrollList: public CTexture, public InputHandler
{
public:
	ScrollList( SDL_Renderer *aRenderer , SDL_Texture* aTexture, SDL_Rect* aRect, int itemsToShow, int aItemWidth, int aItemHeigth );
	ScrollList();
	virtual ~ScrollList();

	void initScrollList(SDL_Renderer *aRenderer, int itemsToShow, int aItemWidth, int aItemHeigth);
	void addItem(CTexture* item);
	void removeItem(int index);
	void scrollWithDirection(int direction);

	void calculateVisibleItemsPositions();

	virtual void draw() override;
	virtual bool onClick(SDL_Point* point) override;
	virtual bool canDrag() const override;
	virtual bool onDrag(int direction) override;
	virtual void ConnectMethod(std::function<bool(int)> method);
	virtual bool containsPoint(int x, int y) const override;

private:
	vector<CTexture*> itemList;
	int itemCountToShow;
	int firstToShow, lastToShow;
	int itemWidth, itemHeight;
	void scrollUtil(int& index, int shift);


protected:
	std::function<bool(int)> connectedMethod;
};


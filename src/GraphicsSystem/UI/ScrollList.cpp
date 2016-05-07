/*
 * ScrollList.cpp
 *
 *  Created on: 19 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "ScrollList.h"
#include <iostream>
ScrollList::ScrollList( SDL_Texture* aTexture, SDL_Rect* aRect, int itemsToShow, int aItemWidth, int aItemHeight )
:CTexture(aTexture), InputHandler(),
 itemCountToShow( itemsToShow ), firstToShow( -1 ), lastToShow( -1),
 itemWidth( aItemWidth ), itemHeight( aItemHeight)
{
	// TODO Auto-generated constructor stub

}

ScrollList::ScrollList()
:CTexture(), InputHandler(),
 itemCountToShow( 0 ), firstToShow( -1 ), lastToShow( -1),
 itemWidth( 0 ), itemHeight( 0)
{
}

void ScrollList::initScrollList( int itemsToShow,
		int aItemWidth, int aItemHeight)
{

    setRect(0, 0, aItemWidth, aItemHeight * itemsToShow);
    itemCountToShow = itemsToShow;
    itemWidth = aItemWidth;
    itemHeight = aItemHeight;
}

ScrollList::~ScrollList()
{
	// TODO Auto-generated destructor stub
}


void ScrollList::addItem(CTexture* item)
{
	if (item != nullptr)
	{
		itemList.push_back(item);
		if (itemList.size() == 1)
		{
			firstToShow = lastToShow = 0;

		}
		else
			if (lastToShow - firstToShow < itemCountToShow - 1)
			{
				++lastToShow;
			}


        item->setRect(0, 0, itemWidth, itemHeight);
	}

}
void ScrollList::removeItem(int index)
{
	if (!itemList.empty())
	{
		if (itemList.size() == 1)
		{
			firstToShow = lastToShow = -1;
		}
		else
		{
			if (lastToShow == itemList.size() - 1)
				--lastToShow;

			if (lastToShow != firstToShow && lastToShow != itemList.size() - 1)
			{
				std::swap(itemList[index], itemList[itemList.size() - 1]);
				//calculateVisibleItemsPositions();
			}


		}


		itemList.pop_back();
		calculateVisibleItemsPositions();

	}
}

void ScrollList::calculateVisibleItemsPositions()
{
	if (!itemList.empty())
	for(int index = firstToShow; index <= lastToShow; ++index)
        itemList[index]->setPosY((index - firstToShow) * itemHeight);

}


void ScrollList::scrollWithDirection(int direction)//TODO:: Wrong Logic
{
	if (direction == 0)
		return;

	int UpOrDown = itemCountToShow * ((direction > 0)? 1 : -1);
	scrollUtil(firstToShow, UpOrDown);
	scrollUtil(lastToShow, UpOrDown);

	std::cout << firstToShow << '\t' << lastToShow << std::endl;
	calculateVisibleItemsPositions();

}


void ScrollList::draw()
{
	if (!itemList.empty())
	for(int i = firstToShow; i <= lastToShow; ++i)
    {

        Renderer::getInstance()->renderTexture(itemList[i]->getTexture(), &itemList[i]->getRect());
    }
//		CTexture::CopyTextureToRenderer( itemList[i]->getTexture(), nullptr, itemList[i]->getRect() );
}

bool ScrollList::onClick(SDL_Point* point)
{
	int n = itemList.size();
	for(int i = 0; i != n; ++i)
        if (SDL_PointInRect(point, &itemList[i]->getRect()))
		{
			if (connectedMethod != nullptr)
			{
				if (connectedMethod(i))
					removeItem(i);
				//calculateVisibleItemsPositions();
			}
			return true;
		}

	return false;
}

void ScrollList::ConnectMethod(std::function<bool(int)> method)
{
	connectedMethod = method;
}

bool ScrollList::canDrag() const
{
	return (itemList.size() > itemCountToShow);
}

bool ScrollList::onDrag(int direction)
{
	scrollWithDirection(direction);
}

bool ScrollList::containsPoint(int x, int y) const
{
	SDL_Point point = { x, y };
    return SDL_PointInRect(&point, &getRect());
}

void ScrollList::scrollUtil(int& index, int shift)//TODO:: Wrong Logic
{

	if (firstToShow == index)
	{
		if (index + shift > itemList.size() - 1)
			return;

		index += shift;
		return;
	}

	index += shift;

	if (index < 0)
		index = 0;
	else
		if (index > itemList.size() - 1)
			index = itemList.size() - 1;

}

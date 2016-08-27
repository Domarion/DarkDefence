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
    clear();
	// TODO Auto-generated destructor stub
}


void ScrollList::addItem(IDrawable* item)
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



        item->setSize(itemWidth, itemHeight);

        item->setPos(getRect().x, getRect().y);

         calculateVisibleItemsPositions();
	}

}
void ScrollList::removeItem(int index)
{
    if (itemList.empty())
        return;
    if (itemList.size() == 1)
    {
        firstToShow = lastToShow = -1;

        IDrawable* backItem = itemList.back();
        itemList.pop_back();
        delete backItem;

        return;

    }

    if (index == itemList.size() - 1)
    {
        --lastToShow;
        IDrawable* backItem = itemList.back();
        itemList.pop_back();
        delete backItem;

        return;
    }

    delete itemList[index];

    for(int i = index; i < itemList.size() - 1; ++i)
        itemList[i] = itemList[i + 1];

    itemList.pop_back();


    if (lastToShow >= itemList.size())
        lastToShow = itemList.size() - 1;


    calculateVisibleItemsPositions();

}

void ScrollList::calculateVisibleItemsPositions()
{
	if (!itemList.empty())
	for(int index = firstToShow; index <= lastToShow; ++index)
    {

        std::cout << "ItemPos y = " << (getRect().y + (index - firstToShow) * itemHeight) << std::endl;
        itemList[index]->setPosY(getRect().y + (index - firstToShow) * itemHeight);
    }



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

void ScrollList::clear()
{
    firstToShow = lastToShow = -1;
    itemCountToShow = 0;
    for(size_t i = 0; i < itemList.size(); ++i)
        delete itemList[i];
    itemList.clear();
}


void ScrollList::draw()
{

    if (getTexture() != nullptr)
        CTexture::draw();

	if (!itemList.empty())
	for(int i = firstToShow; i <= lastToShow; ++i)
    {
       // std::cout << "Item " << "drawn" << std::endl;
        //if (itemList[i]->getTexture() == nullptr)
          //  std::cout << "TEXTURE NULLPTR " << std::endl;
         itemList[i]->draw();
        //Renderer::getInstance()->renderTexture(itemList[i]->getTexture(), &itemList[i]->getRect());
    }
//		CTexture::CopyTextureToRenderer( itemList[i]->getTexture(), nullptr, itemList[i]->getRect() );

}

bool ScrollList::onClick(SDL_Point* point)
{
	int n = itemList.size();
    std::cout << "TouchedAtLeast != nullptr size =" << n << std::endl;


	for(int i = 0; i != n; ++i)
    {
        std::cout << "ScrollItemRect = " << (itemList[i]->getRect().x)<< '\t' << (itemList[i]->getRect().y) << '\t' << (itemList[i]->getRect().w) << '\t' << (itemList[i]->getRect().h)<< std::endl;
         std::cout << "ClickPos = "  << (point->x) << '\t' << (point->y)<< std::endl;

         std::cout << "ItenRect = " << (itemList[i]->getRect().x)
                   << "\t" << (itemList[i]->getRect().y)
                   << "\t" << (itemList[i]->getRect().w)
                   << "\t" << (itemList[i]->getRect().h) << std::endl;
        if (SDL_PointInRect(point, &itemList[i]->getRect()))
		{
			if (connectedMethod != nullptr)
			{

              std::cout << "ScrollConnected != nullptr" << std::endl;

                connectedMethod(i);

				//calculateVisibleItemsPositions();
			}
			return true;
		}
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
    //scrollWithDirection(direction);

    if (direction == 0 || itemList.empty())
        return false;



    if (direction > 0)
        scrollUp();
    else
        scrollDown();

    calculateVisibleItemsPositions();

    return true;
}

bool ScrollList::containsPoint(int x, int y) const
{
	SDL_Point point = { x, y };
    return SDL_PointInRect(&point, &getRect());
}

void ScrollList::scrollUp()
{
    if (lastToShow == itemList.size() - 1)
        return;
    ++firstToShow;
    ++lastToShow;

}

void ScrollList::scrollDown()
{
    if (lastToShow < itemCountToShow)
        return;

    --firstToShow;
    --lastToShow;
}

void ScrollList::setItemWidth(int value)
{
    itemWidth = value;
}

void ScrollList::setItemHeight(int value)
{
    itemHeight = value;
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

/*
 * SlotContainer.cpp
 *
 *  Created on: 28 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "SlotContainer.h"

SlotContainer::SlotContainer(int slotsCount)
:CTexture( nullptr, nullptr, nullptr ), InputHandler(), itemWidth ( 0 ), itemHeight( 0 )
{
	// TODO Auto-generated constructor stub
	slots.resize(slotsCount);
}

SlotContainer::~SlotContainer()
{
	// TODO Auto-generated destructor stub
}

void SlotContainer::draw()
{
	if (!slots.empty())
	for(int i = 0; i < slots.size(); ++i)
		CTexture::CopyTextureToRenderer( slots[i]->getTexture(), nullptr, slots[i]->getRect() );
}

bool SlotContainer::onClick(SDL_Point* point)
{
	int n = slots.size();
	for(int i = 0; i != n; ++i)
		if (SDL_PointInRect(point, slots[i]->getRect()))
		{
			if (connectedMethod != nullptr)
			{
				if (connectedMethod(i))
					removeItem(i);
			}
			return true;
		}

	return false;
}

void SlotContainer::ConnectMethod(std::function<bool(int)> method)
{
	connectedMethod = method;
}

bool SlotContainer::containsPoint(int x, int y) const
{
	SDL_Point point = { x, y };
	return SDL_PointInRect(&point, getRect());
}

void SlotContainer::addItem(CTexture* item, int index)
{
	if (item != nullptr && index >= 0 && index < slots.size())
		slots[index] = item;
}
void SlotContainer::removeItem(int index)
{
	if (index >= 0 && index < slots.size())//TODO: delete Texture?
		slots[index] = nullptr;
}

void SlotContainer::setItemRect(int index, SDL_Rect* rect)
{
	slots[index]->setRect(rect);
}

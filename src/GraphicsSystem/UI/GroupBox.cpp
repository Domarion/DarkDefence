/*
 * GroupBox.cpp
 *
 *  Created on: 26 марта 2016 г.
 *      Author: kostya_hm
 */

#include "GroupBox.h"

GroupBox::GroupBox()
{
	// TODO Auto-generated constructor stub

}

GroupBox::~GroupBox()
{
    // TODO Auto-generated destructor stub
   //  for(int i = 0; i < children.size(); ++i)
     //   delete children[i];
}

bool GroupBox::addChild(CTexture * const child)
{
    if (children.size() == 0)
        child->getRect()->x = getRect()->x;
    else
        child->getRect()->x = children[children.size() - 1]->getRect()->x + children[children.size() - 1]->getRect()->w + 5;
    child->getRect()->y = getRect()->y;
    if (child->getRect()->h > getRect()->h)
        child->getRect()->h = getRect()->h;

    children.push_back(child);
}

bool GroupBox::removeChild(CTexture * const child)
{
    //TODO:stub
}

void GroupBox::draw()
{
    CTexture::draw();
    for(int i = 0; i < children.size(); ++i)
        children[i]->draw();
}


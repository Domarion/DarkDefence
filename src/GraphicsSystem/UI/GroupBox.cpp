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

bool GroupBox::addChild(CTexture * const child, bool vertical)
{
    if (!vertical)
    {

    if (children.size() == 0)
        child->setPosX(getRect().x);
    else
         child->setPosX(children[children.size() - 1]->getRect().x + children[children.size() - 1]->getRect().w + 5);

    child->setPosY(getRect().y);
    }
    else
    {
        if (children.size() == 0)
            child->setPosX(getRect().x);
        else
        {
             child->setPosX(children[children.size() - 1]->getRect().x);

            child->setPosY(children[children.size() - 1]->getRect().y +  children[children.size() - 1]->getRect().h + 5);
        }

    }
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


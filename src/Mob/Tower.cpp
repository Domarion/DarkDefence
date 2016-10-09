#include "Tower.h"



void Tower::connectMethod(std::function<void (Tower *, int, int)> method)
{
    connectedMethod = method;
}

bool Tower::onClick(SDL_Point *point)
{

    SDL_Rect rect = {this->getSprite()->getPosition().x
                     , this->getSprite()->getPosition().y
                     , this->getSprite()->getSize().width
                     , this->getSprite()->getSize().height};
    if (SDL_PointInRect(point, &rect))
    {
        if (connectedMethod != nullptr)
        {
            connectedMethod(this, point->x, point->y);
        }
        return true;
    }
    return false;
}

Tower::Tower(MobModel *model, TileMapManager *aTileMapPtr)
    :Mob(model, aTileMapPtr)
{

}

Tower::~Tower()
{

}



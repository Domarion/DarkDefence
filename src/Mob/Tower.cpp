#include "Tower.h"



void Tower::connectMethod(std::function<void (Tower *, int, int)> method)
{
    connectedMethod = method;
}

bool Tower::onClick(SDL_Point *point)
{
    if (SDL_PointInRect(point, &getSprite()->getRect()))
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



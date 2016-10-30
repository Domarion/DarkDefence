#include "Tower.h"

void Tower::connectMethod(std::function<void(std::shared_ptr<Tower>, int, int)> method)
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
            connectedMethod(std::static_pointer_cast<Tower>(shared_from_this()), point->x, point->y);
        }
        return true;
    }
    return false;
}

Tower::Tower(std::shared_ptr<MobModel> model, std::shared_ptr<TileMapManager> aTileMapPtr)
    :Mob(model, aTileMapPtr)
{

}



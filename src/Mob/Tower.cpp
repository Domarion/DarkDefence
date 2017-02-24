#include "Tower.h"

void Tower::connectMethod(std::function<void(std::shared_ptr<Tower>, int, int)> method)
{
    connectedMethod = method;
}

bool Tower::onClick(Position point)
{

    SDL_Rect rect = {this->getSprite()->getRealPosition().x
                     , this->getSprite()->getRealPosition().y
                     , this->getSprite()->getSize().width
                     , this->getSprite()->getSize().height};
    SDL_Point sPoint{point.x, point.y};

    if (SDL_PointInRect(&sPoint, &rect))
    {
        if (connectedMethod != nullptr)
        {
            connectedMethod(std::static_pointer_cast<Tower>(shared_from_this()), point.x, point.y);
        }
        return true;
    }
    return false;
}

Tower::Tower(std::shared_ptr<MobModel> model, std::shared_ptr<TileMapManager> aTileMapPtr)
    :Mob(model, aTileMapPtr)
{

}



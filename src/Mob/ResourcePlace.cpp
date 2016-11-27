#include "ResourcePlace.h"
#include "../GlobalScripts/GameModel.h"
#include "../Mob/Mine.h"
#include <iostream>
#include "../Input/InputDispatcher.h"
ResourcePlace::ResourcePlace()
    :limit(1000), resourceType(Enums::ResourceTypes::WHEAT)
{

}

ResourcePlace::ResourcePlace(int aLimit, Enums::ResourceTypes aResourceType)
    :limit(aLimit), resourceType(aResourceType)
{

}

ResourcePlace::~ResourcePlace()
{

}

void ResourcePlace::setLimit(int amount)
{
    limit = amount;
}

Enums::ResourceTypes ResourcePlace::getResourceType() const
{
    return resourceType;
}

bool ResourcePlace::onClick(Position point)
{
    if (getSprite() == nullptr)
        return false;

    SDL_Point sPoint{point.x, point.y};

    SDL_Rect rect = {this->getSprite()->getPosition().x
                     , this->getSprite()->getPosition().y
                     , this->getSprite()->getSize().width
                     , this->getSprite()->getSize().height
                    };
    if (SDL_PointInRect(&sPoint, &rect))
    {

           //std::cout << "resType =" << resourceType << std::endl;
        std::unique_ptr<MineModel> tempMineModel = GameModel::getInstance()->getMineModelByRes(resourceType);
        tempMineModel->setLimit(this->limit);
        auto tempMine = std::make_shared<Mine>();

        std::string mineName = tempMineModel->getName();



        tempMine->setMineModel(std::move(tempMineModel));


        auto sprt = std::make_shared<AnimationSceneSprite>(parentScenePtr.lock()->getRenderer());
        sprt->setSize(Size( 90, 120));

        string path = "GameData/textures/Buildings/" + mineName + ".png";
        sprt->loadTexture(path);



        tempMine->setName(mineName);
        tempMine->setTag("Mine");
        tempMine->setSprite(sprt);
         std::cout << "x = " << (this->getX()) << " y = " << (this->getY()) << std::endl;
        parentScenePtr.lock()->spawnObject(this->getX(), this->getY(), tempMine);

        parentScenePtr.lock()->destroyObject(shared_from_this());
        return true;
    }
    return false;
}



bool ResourcePlace::update(double)
{
    return true;
}

void ResourcePlace::finalize()
{

}

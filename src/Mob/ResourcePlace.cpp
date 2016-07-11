#include "ResourcePlace.h"
#include "../GlobalScripts/GameModel.h"
#include "../Mob/Mine.h"
#include <iostream>
#include "../Input/InputDispatcher.h"
ResourcePlace::ResourcePlace()
    :limit(1000), resourceType(Enums::ResourceTypes::WHEAT)
{

}

ResourcePlace::~ResourcePlace()
{

}

void ResourcePlace::setLimit(int amount)
{
    limit = amount;
}

bool ResourcePlace::onClick(SDL_Point *point)
{
    if (getSprite() == nullptr)
        return false;

    if (SDL_PointInRect(point, &getSprite()->getRect()))
    {

           std::cout << "resType =" << resourceType << std::endl;
         MineModel* tempMineModel = GameModel::getInstance()->getMineModelByRes(resourceType);
        tempMineModel->setLimit(this->limit);
        Mine * tempMine = new Mine();
        tempMine->setMineModel(tempMineModel);



       AnimatedSprite* sprt = new AnimatedSprite();
        sprt->setRect(0,0, 90, 120);
        string s1 = "GameData/textures/Buildings/" +tempMineModel->getName() + ".png";
        std::cout << s1 << std::endl;
        sprt->loadTexture(s1);


        if (sprt->getTexture() == nullptr)
            std::cout << "NULLMILL" <<std::endl;
        tempMine->setName("WindMill");
        tempMine->setTag("Mine");
        tempMine->setSprite(sprt);
         std::cout << "x = " << (this->getX()) << " y = " << (this->getY()) << std::endl;
        parentScenePtr->spawnObject(this->getX(), this->getY(), tempMine);

        parentScenePtr->destroyObject(this);
        return true;
    }
    return false;
}



bool ResourcePlace::update(double timestep)
{
    return true;
}

void ResourcePlace::finalize()
{

}

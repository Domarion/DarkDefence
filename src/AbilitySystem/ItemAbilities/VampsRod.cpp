#include "VampsRod.h"
#include "../AbilityShrink.h"
#include "../../Scenes/GameScene.h"

VampsRod::VampsRod()
{

}

VampsRod::~VampsRod()
{

}

void VampsRod::init(std::shared_ptr<Scene> scenePtr)
{
    ManaGlobal* manamodel = GameModel::getInstance()->getManaModel();

    int manaMax = manamodel->getLimit() + 50;
     manamodel->setLimit(manaMax);

     auto gameScenePtr = std::dynamic_pointer_cast<GameScene>(scenePtr);
     if (gameScenePtr == nullptr)
         return;
    map<string, std::shared_ptr<AbilityModel>> models = gameScenePtr->getAbilityModelList();

    for(auto ptr = models.begin(); ptr!= models.end(); ++ptr)
    {
        if (ptr->first == "Shrink")
        {
            std::shared_ptr<AbilityShrink> shrink = std::dynamic_pointer_cast<AbilityShrink>(ptr->second);
//            AbilityShrink* shrink = dynamic_cast<AbilityShrink*>(ptr->second);
            if (shrink != nullptr)
            {
                double dps =  4 * shrink->getDamagePerSecond();
                shrink->setDamagePerSecond(dps);
                double cooldown = shrink->getCooldownTime() *0.5;
                shrink->setCooldownTime(cooldown);
            }
        }
        else
        {
            int manaCost = 2 * ptr->second->getManaCost();
            ptr->second->setManaCost(manaCost);
        }
    }





}

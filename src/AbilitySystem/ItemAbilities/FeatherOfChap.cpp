#include "FeatherOfChap.h"
#include "../../GlobalScripts/GameModel.h"
FeatherOfChap::FeatherOfChap()
    :amount(1000)
{

}

FeatherOfChap::~FeatherOfChap()
{

}

void FeatherOfChap::init(Scene * const scenePtr)
{
    for(int i = 0; i < ResourcesModel::resourceTypeCount; ++i)
        GameModel::getInstance()->getResourcesModel()->increaseLimit(i, amount);
}

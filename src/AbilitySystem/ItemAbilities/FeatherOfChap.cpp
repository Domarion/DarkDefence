#include "FeatherOfChap.h"
#include "../../GlobalScripts/GameModel.h"
FeatherOfChap::FeatherOfChap()
    : amount(1000)
{

}

FeatherOfChap::~FeatherOfChap()
{

}

void FeatherOfChap::init(std::shared_ptr<Scene> scenePtr, std::shared_ptr<ManaGlobal> aManaModel)
{
    for(int i = 0; i < GlobalConstants::resourceTypeCount; ++i)
        GameModel::getInstance()->getResourcesModel()->increaseLimit(i, amount);
}

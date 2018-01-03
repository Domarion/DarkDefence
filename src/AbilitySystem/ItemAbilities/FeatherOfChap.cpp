#include "FeatherOfChap.h"
#include "../../GlobalScripts/GameModel.h"

void FeatherOfChap::init(std::shared_ptr<Scene> /*scenePtr*/, std::shared_ptr<ManaGlobal> /*aManaModel*/)
{
    for(size_t i = 0; i < GlobalConstants::resourceTypeCount; ++i)
        GameModel::getInstance()->getResourcesModel()->increaseLimit(i, amount);
}

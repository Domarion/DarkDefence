#include "IceTalisman.h"

IceTalisman::IceTalisman()
{

}

IceTalisman::~IceTalisman()
{

}

void IceTalisman::init(std::shared_ptr<Scene> scenePtr, std::shared_ptr<ManaGlobal> aManaModel)
{
    int newRegenValue = aManaModel->getRegenValue() - 2;
    aManaModel->setRegenValue(newRegenValue);

    int newMaxMana = aManaModel->getLimit() + 150;
    aManaModel->setLimit(newMaxMana);
}

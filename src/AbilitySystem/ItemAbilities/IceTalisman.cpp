#include "IceTalisman.h"

IceTalisman::IceTalisman()
{

}

IceTalisman::~IceTalisman()
{

}

void IceTalisman::init(std::shared_ptr<Scene> scenePtr)
{
    ManaGlobal* manaModelPtr = GameModel::getInstance()->getManaModel();

    int newRegenValue = manaModelPtr->getRegenValue() - 2;
    manaModelPtr->setRegenValue(newRegenValue);

    int newMaxMana = manaModelPtr->getLimit() + 150;
    manaModelPtr->setLimit(newMaxMana);
}

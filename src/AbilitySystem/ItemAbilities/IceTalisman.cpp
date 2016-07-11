#include "IceTalisman.h"

IceTalisman::IceTalisman()
{

}

IceTalisman::~IceTalisman()
{

}

void IceTalisman::init(Scene* const scenePtr)
{
    ManaGlobal* manaModelPtr = GameModel::getInstance()->getManaModel();

    int newRegenValue = manaModelPtr->getRegenValue() - 2;
    manaModelPtr->setRegenValue(newRegenValue);

    int newMaxMana = manaModelPtr->getLimit() + 150;
    manaModelPtr->setLimit(newMaxMana);
}

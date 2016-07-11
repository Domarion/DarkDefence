#include "UberionsCloak.h"

UberionsCloak::UberionsCloak()
{

}

UberionsCloak::~UberionsCloak()
{

}

void UberionsCloak::init(Scene* const scenePtr)
{
    ManaGlobal* manaModelPtr = GameModel::getInstance()->getManaModel();
    int newRegenValue = manaModelPtr->getRegenValue() + 10;
    manaModelPtr->setRegenValue(newRegenValue);
    int newMaxMana = manaModelPtr->getLimit() + 50;
    manaModelPtr->setLimit(newMaxMana);

    double newPointsModifier = GameModel::getInstance()->getPointsRefundModifier() + 0.2;
    GameModel::getInstance()->setPointsRefundModifier(newPointsModifier);
}

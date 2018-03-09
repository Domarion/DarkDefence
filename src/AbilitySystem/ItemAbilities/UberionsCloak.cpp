#include "UberionsCloak.h"

void UberionsCloak::init(std::shared_ptr<Scene> /*scenePtr*/, std::shared_ptr<ManaGlobal> aManaModel)
{
    int newRegenValue = aManaModel->getRegenValue() + 10;
    aManaModel->setRegenValue(newRegenValue);
    int newMaxMana = aManaModel->getLimit() + 50;
    aManaModel->setLimit(newMaxMana);

    double newPointsModifier = GameModel::getInstance()->getPointsRefundModifier() + 0.2;
    GameModel::getInstance()->setPointsRefundModifier(newPointsModifier);
}

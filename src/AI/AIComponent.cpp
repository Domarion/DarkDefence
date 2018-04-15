#include <algorithm>
#include <cassert>

#include "AIComponent.h"
#include "../Utility/textfilefunctions.h"
#include "../Mob/ArrowAnim.h"
#include "../GlobalScripts/ResourceManager.h"
#include "Logging/Logger.h"
#include "../AbilitySystem/MobAbilities/MobAbilitiesMaker.h"

AIComponent::AIComponent(std::weak_ptr<Mob> aMob)
    : MobPtr(aMob)
    , aiMobState(AIMobStates::aiSEARCH)
    , currentTargetPosition{-1, -1}
    , nextCell{-1, -1}

{
    initMobAbilities();
}

void AIComponent::MakeDecision(double timestep)
{
    auto mobPtr = MobPtr.lock();
    if (mobPtr->getDestructibleObject() && !mobPtr->getDestructibleObject()->IsAlive())
    {
        return;
    }

    switch(aiMobState)
    {
    case AIMobStates::aiSEARCH:
        Search();
        break;
    case AIMobStates::aiSELECT:
        Select();
        break;
    case AIMobStates::aiMOVE:
        MovetoTile(timestep);
        break;
    case AIMobStates::aiATTACK:
        Attack();
        break;
    case AIMobStates::aiRELOAD:
        Reload(timestep);
        break;

    default:
        break;
    }
    Cast(mobPtr);
    for(auto& abilityPtr : mobAbilities)
        if (abilityPtr != nullptr)
            abilityPtr->update(timestep);
}

std::shared_ptr<SceneObject> AIComponent::getCurrentTarget()
{
    return currentTarget;
}

void AIComponent::Search()
{
    auto lockedMob = MobPtr.lock();
    enemiesInfoList = lockedMob->getModel()->getEnemyTags();

    for(const auto& enemyInfo : enemiesInfoList)
    {
        auto lst = lockedMob->getParentScene()->findObjectsByTag(enemyInfo.getTag());
        if (!lst || lst->empty())
            continue;
        avaliableTargets.insert(avaliableTargets.end(), lst->begin(), lst->end());
    }

    if (!avaliableTargets.empty())
        aiMobState = AIMobStates::aiSELECT;
}

void AIComponent::Select()
{
    currentTarget.reset();

    if (avaliableTargets.empty())
    {
        aiMobState = AIMobStates::aiSEARCH;
        return;
    }

    int closestDistanceSqr = 0;
    int maxPriority = 0;

    size_t avaliableSize = avaliableTargets.size();
    size_t invalidTargetCount = 0;

    auto tilemapPtr = MobPtr.lock()->getTileMapManager();

    for (const auto& target: avaliableTargets)
    {
        if (!target || !target->getDestructibleObject())
        {
            ++invalidTargetCount;
            continue;
        }

        bool IsReachable = tilemapPtr && !tilemapPtr->IsFilledCell(target->getPosition());

        bool isTargetAlive = target->getDestructibleObject()->IsAlive();

        if (!IsReachable || !isTargetAlive)
        {
            ++invalidTargetCount;
            continue;
        }

        if (!target->isVisible())
        {
            continue;
        }

        int distanceSqr = MobPtr.lock()->computeDistanceSqr(target);
        int priority = getPriorityFromTag(target->getTag());

        if (priority > maxPriority || (priority == maxPriority && distanceSqr < closestDistanceSqr))
        {
            maxPriority = priority;
            closestDistanceSqr = distanceSqr;
            currentTarget = target;
        }
    }

    if (avaliableSize == invalidTargetCount)
    {
        aiMobState = AIMobStates::aiSEARCH;
        return;
    }

    if (currentTarget)
    {
        MobPtr.lock()->getSprite()->setCurrentState("walk");
        aiMobState = AIMobStates::aiMOVE;
    }
}

void AIComponent::Attack()
{
    bool hasNotAvaliableTarget =
            !currentTarget
            || !currentTarget->getDestructibleObject()
            || !currentTarget->getDestructibleObject()->IsAlive();

    if (hasNotAvaliableTarget)
    {
        aiMobState = AIMobStates::aiSELECT;
        return;
    }

    if (UseAbility())
    {
        return;
    }

    auto damage = MobPtr.lock()->getModel()->getAttackDamage();

    for(const auto& damageVal : damage)
    {
        if (damageVal > 0)
        {
            ShotArrow();
            break;
        }
    }

    if (currentTarget->getDestructibleObject()->receiveDamage(damage))
    {
        avaliableTargets.remove(currentTarget);
        currentTarget = nullptr;
    }
    else
    {
        Cast(currentTarget);
    }

    MobPtr.lock()->getModel()->reload();
    aiMobState = AIMobStates::aiRELOAD;
}

void AIComponent::Reload(double timestep)
{
    if (MobPtr.lock()->getModel()->IsReloadingInProgress())
    {
        MobPtr.lock()->getModel()->ProcessReloadStep(timestep);
        return;
    }

    aiMobState = (!currentTarget)? AIMobStates::aiSELECT : AIMobStates::aiATTACK;

    if (aiMobState == AIMobStates::aiATTACK)
    {
        MobPtr.lock()->getSprite()->setCurrentState("attack");
    }
}

void AIComponent::MovetoTile(double timestep)
{
    const static pair<int, int> emptyCell = std::make_pair(TileMapManager::EmptyCell, TileMapManager::EmptyCell);
    if (!currentTarget)
    {
        aiMobState = AIMobStates::aiSELECT;
        nextCell = emptyCell;
        return;
    }

    auto tilemapPtr = MobPtr.lock()->getTileMapManager();

    if (!tilemapPtr)
    {
        LOG_ERROR("AIComponent::MovetoTile. Tilemap is nullptr");
        return;
    }

    pair<int, int> mobPos = tilemapPtr->getPosFromGlobalCoords(MobPtr.lock()->getPosition());
    pair<int, int> targetPos = tilemapPtr->getPosFromGlobalCoords(currentTarget->getPosition());

    if (distanceSquareInRange(mobPos, targetPos))
    {
        aiMobState = AIMobStates::aiATTACK;
        MobPtr.lock()->getSprite()->setCurrentState("attack");

        nextCell = emptyCell;
        currentPath.reset();
        return;
    }

    Cast(currentTarget);

    if ((MobPtr.lock()->getTag() == "Tower"))
    {
        return;
    }

    if (currentTargetPosition != targetPos || !currentPath || currentPath->empty())
    {
        nextCell = emptyCell;
        currentTargetPosition = targetPos;
        bool canBuildPath = tilemapPtr->waveAlgo(mobPos, targetPos);
        if (canBuildPath)
        {
            currentPath = tilemapPtr->getPath(targetPos);
        }
        else
        {
            aiMobState = AIMobStates::aiSELECT;
            return;
        }
    }

    if (nextCell == emptyCell)
    {
        nextCell = currentPath->back();
        currentPath->pop_back();
    }

    if (nextCell == mobPos)
    {
        if (currentPath == nullptr)
        {
            return;
        }
        auto it = std::find(currentPath->begin(), currentPath->end(), mobPos);

        while (it != currentPath->end())
        {
            currentPath->erase(it++);
        }

        if (!currentPath->empty())
        {
            nextCell = currentPath->back();
        }
    }

    if (nextCell != mobPos && nextCell != emptyCell)
    {
        auto globalCoords = tilemapPtr->getGlobalPosFromLocalCoords(nextCell);

        MoveToPos(timestep, globalCoords);
    }
}

void AIComponent::MoveToPos(double /*timestep*/, Position targetPoint)
{
    // Примем, что timestep = 1 вместо 16 для удобной записи скорости.

    assert(MobPtr.lock()->getModel() != nullptr);

    auto speedWithModifier = MobPtr.lock()->getModel()->getMoveSpeed();
    int speed = static_cast<int>(speedWithModifier.first + speedWithModifier.second);
    Position newMobPos{MobPtr.lock()->getPosition()};

    int diffX = targetPoint.x  - newMobPos.x;
    int diffY = targetPoint.y  - newMobPos.y;

    int signumX = signum(diffX);
    int signumY = signum(diffY);

    newMobPos.x += (abs(diffX) < speed)? diffX : signumX * speed;
    newMobPos.y += (abs(diffY) < speed)? diffY : signumY * speed;

    auto spritePtr = MobPtr.lock()->getModifiableSprite();

    if (signumX <= 0)
    {
        int flip = (MobPtr.lock()->getName() == "Spider")? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
        spritePtr->setFlipping(flip);
    }
    else
    {
        int flip = (MobPtr.lock()->getName() != "Spider")? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
        spritePtr->setFlipping(flip);
    }

    MobPtr.lock()->setPosition(newMobPos);
}


bool AIComponent::distanceSquareInRange(const pair<int, int>& firstPoint, const pair<int, int>& secondPoint)
{
    int diffX = secondPoint.first - firstPoint.first;
    int diffY = secondPoint.second - firstPoint.second;
    int current_distanceSqr = diffX*diffX + diffY*diffY;
    int attackDistanceSqr = static_cast<int>(MobPtr.lock()->getModel()->getAttackDistance().first);
    attackDistanceSqr *= attackDistanceSqr;
    return current_distanceSqr <= attackDistanceSqr;
}

int AIComponent::signum(int aValue) const
{
    if (aValue == 0)
        return 0;

    return aValue > 0 ? 1 : -1;
}

int AIComponent::getPriorityFromTag(const string& aTag)
{
    for(const auto& enemyInfo: enemiesInfoList)
        if (enemyInfo.getTag() == aTag)
            return enemyInfo.getPriority();
    return -1;
}

Enums::EReaction AIComponent::getReactionByTag(const string& aTag)
{
    for(const auto& enemyInfo: enemiesInfoList)
        if (enemyInfo.getTag() == aTag)
            return enemyInfo.getReaction();

    return Enums::EReaction::Attack;
}

bool AIComponent::Cast(const std::shared_ptr<SceneObject>& aTarget)
{
    for(auto& abilityPtr : mobAbilities)
        if (abilityPtr != nullptr &&
                abilityPtr->canTrigger(aTarget, aiMobState))
        {
            return abilityPtr->setAsReady();
        }

    return false;
}

bool AIComponent::CanCast(const std::shared_ptr<SceneObject>& aTarget) const
{
    for(auto& abilityPtr : mobAbilities)
        if (abilityPtr != nullptr &&
                abilityPtr->canTrigger(aTarget, aiMobState))
        {
            return true;
        }
    return false;
}

void AIComponent::ShotArrow()
{
    auto lockedMob = MobPtr.lock();
    if (lockedMob->getTag() == "Tower")
    {
        const std::string& arrowName = lockedMob->getModel()->getArrowName();

        auto lockedParentScene = MobPtr.lock()->getParentScene();
        if (!arrowName.empty())
        {
            std::shared_ptr<AnimationSceneSprite> sprite = nullptr;

            if (ResourceManager::getInstance()->hasAnimationPack(arrowName))
            {
                auto& animPack = ResourceManager::getInstance()->getAnimationPack(arrowName);
                sprite =
                    std::make_shared<AnimationSceneSprite>(
                        lockedParentScene->getRenderer(),
                        AnimationSceneSprite::Animation{animPack});
            }
            else
            {
                sprite = std::make_shared<AnimationSceneSprite>(
                    lockedParentScene->getRenderer());
            }

            assert(sprite);

            sprite->setTexture(ResourceManager::getInstance()->getTexture(arrowName));

            auto miniObject = std::make_shared<ArrowAnim>(currentTarget->getRealPosition());
            miniObject->setSprite(sprite);
            miniObject->setDrawPriority(lockedMob->getDrawPriority() + 1);
            lockedParentScene->spawnObject(lockedMob->getRealPosition(), miniObject);
        }
    }
}

bool AIComponent::UseAbility()
{
    EReaction reaction = getReactionByTag(currentTarget->getTag());
    if (reaction == EReaction::UseAbilities)
    {
        Cast(currentTarget);

        avaliableTargets.remove(currentTarget);
        currentTarget = nullptr;
        aiMobState = AIMobStates::aiSELECT;
        return true;
    }

    return false;
}

void AIComponent::initMobAbilities() // TODO Load settings from files.
{
    list<string> mobAbilitiesNames =  MobPtr.lock()->getModel()->getAbilitiesNames();

    for(const auto& abilityName : mobAbilitiesNames)
    {
        mobAbilities.emplace_back(MakeMobAbilityByName(abilityName));
        mobAbilities.back()->setWorkTime(4000);
        mobAbilities.back()->setCooldownTime(8000);
        mobAbilities.back()->init(MobPtr.lock()->getParentScene());
    }
}


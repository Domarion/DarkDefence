#include "AbilityMultitargetObject.hpp"
#include <algorithm>
#include "GlobalScripts/ResourceManager.h"

AbilityMultitargetObject::AbilityMultitargetObject(size_t aTargetCount)
    : SceneObject()
    , mTargetCount(aTargetCount)
{
}

bool AbilityMultitargetObject::update(double aTimeStep)
{
    switch (mState)
    {
    case StateT::CollectTargets:
        CollectTargets();
        break;
    case StateT::ProcessTargets:
        ProcessTargets();
        break;
    case StateT::Move:
        MoveToTarget();
        break;
    case StateT::EndWork:
        EndWork();
        return false;
    default:
        break;
    }

    return SceneObject::update(aTimeStep);
}

void AbilityMultitargetObject::SetCallBack(AbilityMultitargetObject::CallBackT aHandler)
{
    mCallBack = aHandler;
}

void AbilityMultitargetObject::CollectTargets()
{
    auto parentSceneShared = parentScenePtr.lock();

    if (!parentSceneShared)
    {
        mState = StateT::EndWork;
        return;
    }

    auto allMonsters = parentSceneShared->findObjectsByTag("Monster");

    if (!allMonsters || allMonsters->empty())
    {
        mState = StateT::EndWork;
        return;
    }

    mState = StateT::ProcessTargets;

    if (allMonsters->size() <= mTargetCount)
    {
        mTargetCount = allMonsters->size();
        mTargets = std::move(allMonsters);
        return;
    }

    mTargets = std::make_unique<SceneObjectList>();
    std::copy_n(allMonsters->begin(), mTargetCount, std::back_inserter(*mTargets));
}

void AbilityMultitargetObject::ProcessTargets()
{
    if (!mTargets || mTargets->empty())
    {
        mState = StateT::EndWork;
        return;
    }

    auto& firstMonster = mTargets->front();
    bool isMonsterExistsAndAlive = firstMonster
        && firstMonster->getDestructibleObject()&& firstMonster->getDestructibleObject()->IsAlive();

    if (!isMonsterExistsAndAlive)
    {
        mTargets->pop_front();
        return;
    }

    mState = StateT::Move;
}

void AbilityMultitargetObject::EndWork()
{
    mTargets.reset();

    // Отправляем пустой указатель для завершения работы способности.
    if (mCallBack)
    {
        mCallBack(nullptr);
    }
}

void AbilityMultitargetObject::MoveToTarget()
{
    auto signum = [](int aValue) -> int
        {
            if (aValue == 0)
            {
                return 0;
            }

            return aValue > 0 ? 1 : -1;
        };

    auto firstMonster = mTargets->front();

    auto targetPos = firstMonster->getPosition();
    auto newSelfPos{getPosition()};

    int diffX = targetPos.x - newSelfPos.x;
    int diffY = targetPos.y - newSelfPos.y;

    int speed = 7;

    if (abs(diffX) < speed && abs(diffX) < speed)
    {
        if (mCallBack)
        {
            mCallBack(firstMonster);
        }

        mTargets->pop_front();
        mState = (!mTargets->empty())? StateT::ProcessTargets : StateT::EndWork;
        return;
    }


    int signumX = signum(diffX);
    int signumY = signum(diffY);

    newSelfPos.x += (abs(diffX) < speed)? diffX : signumX * speed;
    newSelfPos.y += (abs(diffY) < speed)? diffY : signumY * speed;

    setPosition(newSelfPos);
}

std::shared_ptr<AbilityMultitargetObject> Make_AbilityMultitargetObject(
    const std::string& aName,
    size_t aTargetCount,
    std::shared_ptr<RenderingSystem>& aRenderer)
{
    auto object = std::make_shared<AbilityMultitargetObject>(aTargetCount);
    if (object == nullptr)
    {
        return nullptr;
    }

    auto& animPack = ResourceManager::getInstance()->getAnimationPack(aName);
    auto sprite = std::make_shared<AnimationSceneSprite>(aRenderer, AnimationSceneSprite::Animation{animPack});

    if (sprite == nullptr)
    {
        return nullptr;
    }

    sprite->setTexture(ResourceManager::getInstance()->getTexture(aName));

    object->setSprite(sprite);

    return object;
}

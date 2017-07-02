/*
 * AIComponent.cpp
 *
 *  Created on: 8 марта 2016 г.
 *      Author: kostya_hm
 */

#include "AIComponent.h"
#include "../GlobalScripts/GameModel.h"
#include <cassert>
#include <algorithm>
#include "../Utility/textfilefunctions.h"
#include "../Mob/ArrowAnim.h"

AIComponent::AIComponent(std::weak_ptr<Mob> aMob)
    : MobPtr(aMob)
    , aiMobState(AIMobStates::aiSEARCH)
    , currentTarget(nullptr)
    , currentTargetPosition{-1, -1}
    , nextCell{-1, -1}

{
    initMobAbilities();
}

void AIComponent::MakeDecision(double timestep)
{
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
    Cast(MobPtr.lock());
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
    enemiesInfoList = MobPtr.lock()->getModel()->getEnemyTags();
    for(const auto& enemyInfo : enemiesInfoList)
    {
        auto lst = MobPtr.lock()->getParentScene()->findObjectsByTag(enemyInfo.getTag());
        if (lst == nullptr || lst->empty())
            continue;
        avaliableTargets.insert(avaliableTargets.end(), lst->begin(), lst->end());
    }


    if (!avaliableTargets.empty())
        aiMobState = AIMobStates::aiSELECT;

}

void AIComponent::Select()
{
	if (!avaliableTargets.empty())
	{
		int closestDistanceSqr = 0;
        int maxPriority = 0;
        for(auto& target: avaliableTargets)
		{

            if (target == nullptr || !target->isVisible())
                continue;
            int distanceSqr = MobPtr.lock()->computeDistanceSqr(target);
            int priority = getPriorityFromTag(target->getTag());
            if (priority > maxPriority || (priority == maxPriority && distanceSqr < closestDistanceSqr))
			{
                maxPriority = priority;
				closestDistanceSqr = distanceSqr;
                currentTarget = target;
			}
		}
	}

	if (currentTarget == nullptr)
		aiMobState = AIMobStates::aiSEARCH;
	else
		aiMobState = AIMobStates::aiMOVE;
}


void AIComponent::Attack()
{
    if (currentTarget == nullptr)
		aiMobState = AIMobStates::aiSELECT;
	else
	{
        EReaction reaction = getReactionByTag(currentTarget->getTag());
       if (reaction == EReaction::UseAbilities)
       {

           Cast(currentTarget);

           avaliableTargets.remove(currentTarget);
           currentTarget = nullptr;
           aiMobState = AIMobStates::aiSELECT;
       }
       else
       {
           int* damage = MobPtr.lock()->getModel()->getAttackDamage();

           if (damage == nullptr)
           {
               return;
           }

           bool hasDamage = false;

           for(int i = 0; i < DestructibleObject::damageTypesCount; ++i)
           {
               if (damage[i] > 0)
               {
                   hasDamage = true;
                   break;
               }
           }

           if (hasDamage && MobPtr.lock()->getTag() == "Tower")
           {
                auto sprite = std::make_shared<AnimationSceneSprite>(MobPtr.lock()->getParentScene()->getRenderer());
                sprite->loadTexture("GameData/textures/Arrows/arrowSheet.png");
                sprite->setSize(Size{123, 47});
                map<string, vector<SDL_Rect> > anims;

                std::string filename = "GameData/anims/Arrows/arrow.anim";
                androidText::setRelativePath(filename);
                androidText::loadAnimFromFile(filename, anims);

                for(auto& anim : anims)
                {
                sprite->setAnimRects(anim.first, anim.second);
                }

                auto miniObject = std::make_shared<ArrowAnim>(currentTarget->getRealPosition());
                miniObject->setSprite(sprite);
                MobPtr.lock()->getParentScene()->spawnObject(
                    MobPtr.lock()->getRealPosition().x, MobPtr.lock()->getRealPosition().y, miniObject);
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
           delete[] damage;

           MobPtr.lock()->getModel()->reload();
           aiMobState = AIMobStates::aiRELOAD;
       }
	}
}

void AIComponent::Reload(double timestep)
{
    if (MobPtr.lock()->getModel()->getReloadTime() > 0)
        MobPtr.lock()->getModel()->setReloadTime(MobPtr.lock()->getModel()->getReloadTime() - timestep);
	else
	{
        aiMobState = (currentTarget == nullptr)? AIMobStates::aiSELECT : AIMobStates::aiATTACK;
	}
}



void AIComponent::MovetoTile(double timestep)
{

   const static pair<int, int> emptyCell = std::make_pair(TileMapManager::EmptyCell, TileMapManager::EmptyCell);
    if (currentTarget == nullptr)
    {
        aiMobState = AIMobStates::aiSELECT;
        nextCell = emptyCell;
        return;

    }

    auto tilemapPtr = MobPtr.lock()->getTileMapManager();

    if (tilemapPtr == nullptr)
    {
        std::cout << "tilemap is null, baby" << std::endl;
        return;
    }

    pair<int, int> mobPos = tilemapPtr->getPosFromGlobalCoords(MobPtr.lock()->getPosition());
    pair<int, int> targetPos = tilemapPtr->getPosFromGlobalCoords(currentTarget->getPosition());

    if (distanceInRange(mobPos, targetPos))
    {
        aiMobState = AIMobStates::aiATTACK;
        nextCell = emptyCell;
        currentPath.reset();
        return;
    }

    Cast(currentTarget);

    if ((MobPtr.lock()->getTag() == "Tower"))
    {
        return;
    }

    if (currentTargetPosition != targetPos || currentPath == nullptr || currentPath->empty())
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


bool AIComponent::distanceInRange(const pair<int, int> &firstPoint, const pair<int, int> &secondPoint)
{
    int diffX = secondPoint.first - firstPoint.first;
    int diffY = secondPoint.second - firstPoint.second;
    int current_distance = diffX*diffX + diffY*diffY;
    int attackDistance = static_cast<int>(MobPtr.lock()->getModel()->getAttackDistance().first);

    return current_distance <= attackDistance;
}

int AIComponent::signum(int aValue) const
{
    if (aValue == 0)
        return 0;

    return aValue > 0 ? 1 : -1;
}

int AIComponent::getPriorityFromTag(const string &aTag)
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

bool AIComponent::Cast(std::shared_ptr<SceneObject> target)
{
    for(auto& abilityPtr : mobAbilities)
        if (abilityPtr != nullptr &&
            abilityPtr->canTrigger(target, aiMobState))
        {
            return abilityPtr->setAsReady();
        }

    return false;
}

bool AIComponent::CanCast(std::shared_ptr<SceneObject> target)
{
    for(auto& abilityPtr : mobAbilities)
        if (abilityPtr != nullptr &&
            abilityPtr->canTrigger(target, aiMobState))
        {
            return true;
        }
    return false;
}

void AIComponent::initMobAbilities()
{

    list<string> mobAbilitiesNames =  MobPtr.lock()->getModel()->getAbilitiesNames();

    for(auto ptr = mobAbilitiesNames.begin(); ptr != mobAbilitiesNames.end(); ++ptr)
    {

//        std::cout << *ptr << std::endl;
        mobAbilities.emplace_back(std::move(GameModel::getInstance()->getMobAbilityByName(*ptr)));
        mobAbilities.back()->setWorkTime(4000);
        mobAbilities.back()->setCooldownTime(4000);
        mobAbilities.back()->init(MobPtr.lock()->getParentScene());
    }
}


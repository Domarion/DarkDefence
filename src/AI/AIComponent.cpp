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
//     std::cout << (MobPtr.lock()->getModel()->getName()) << std::endl;
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

    if ((MobPtr.lock()->getTag() == "Tower"))
    {
        return;
    }
//    std::cout << "MOBPOS = {" << mobPos.first << ", " << mobPos.second
//              << "} TARGETPOS {" << targetPos.first << ", " << targetPos.second << std::endl;


    if (currentTargetPosition != targetPos || currentPath == nullptr || currentPath->empty())
    {
        nextCell = emptyCell;
        currentTargetPosition = targetPos;
        bool canBuildPath = tilemapPtr->waveAlgo(mobPos, targetPos);
        if (canBuildPath)
        {
            currentPath = tilemapPtr->getPath(targetPos);

//            std::cout << "New Path {" << std::endl;
//            int index = 0;
//            for(const auto& item : *currentPath)
//            {
//                std::cout << index << "\t" << item.first << "\t" << item.second << std::endl;
//                index++;
//            }

        }
        else
        {
            aiMobState = AIMobStates::aiSELECT;
            return;
        }
    }


    if (nextCell == emptyCell)
    {
//        std::cout << "nextCell" << std::endl;
        nextCell = currentPath->back();
        currentPath->pop_back();
    }

    if (nextCell == mobPos)
    {
        if (currentPath == nullptr)
        {
            return;
        }

//        std::cout << "Path {" << std::endl;
//        int index = 0;
//        for(const auto& item : *currentPath)
//        {
//            std::cout << index << "\t" << item.first << "\t" << item.second << std::endl;
//            index++;
//        }


        auto it = std::find(currentPath->begin(), currentPath->end(), mobPos);

        while (it != currentPath->end())
        {
            currentPath->erase(it++);
        }

        if (!currentPath->empty())
        {
            nextCell = currentPath->back();
        }
//        bool canBuildPath = tilemapPtr->waveAlgo(mobPos, targetPos);

//        if (canBuildPath)
//        {
//            nextCell = path->back();
//        }
//        else
//        {
//            nextCell = emptyCell;
//            aiMobState = AIMobStates::aiSELECT;
//        }
    }

    if (nextCell != mobPos && nextCell != emptyCell)
    {
//        std::cout << "Current pos " << mobPos.first << "\t" << mobPos.second
//            << " next cell " << nextCell.first << "\t" << nextCell.second << std::endl;
        auto globalCoords = tilemapPtr->getGlobalPosFromLocalCoords(nextCell);
//        std::cout << "Global coords next cell " << globalCoords << std::endl;

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

    int signumX = signum(targetPoint.x  - newMobPos.x);
    newMobPos.x += signumX * speed;
    newMobPos.y += signum(targetPoint.y  - newMobPos.y) * speed;

    auto spritePtr = MobPtr.lock()->getModifiableSprite();

    if (signumX <= 0)
    {
        spritePtr->setFlipping(SDL_FLIP_HORIZONTAL);
    }
    else
    {
        spritePtr->setFlipping(SDL_FLIP_NONE);
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

Enums::EReaction AIComponent::getReactionByTag(const string &aTag)
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
            abilityPtr->setAsReady();
            return true;
        }


    return false;
}

void AIComponent::initMobAbilities()
{

    list<string> mobAbilitiesNames =  MobPtr.lock()->getModel()->getAbilitiesNames();

    for(auto ptr = mobAbilitiesNames.begin(); ptr != mobAbilitiesNames.end(); ++ptr)
    {

        std::cout << *ptr << std::endl;
        mobAbilities.emplace_back(std::move(GameModel::getInstance()->getMobAbilityByName(*ptr)));
        mobAbilities.back()->setWorkTime(4000);
        mobAbilities.back()->setCooldownTime(4000);
        mobAbilities.back()->init(MobPtr.lock()->getParentScene());
    }
}


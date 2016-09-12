/*
 * AIComponent.cpp
 *
 *  Created on: 8 марта 2016 г.
 *      Author: kostya_hm
 */

#include "AIComponent.h"
#include "../GlobalScripts/GameModel.h"


AIComponent::~AIComponent()
{
	// TODO Auto-generated destructor stub
}

AIComponent::AIComponent(Mob *aMob)
:MobPtr(aMob), aiMobState(AIMobStates::aiSEARCH), currentTarget(nullptr)

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
    Cast(MobPtr);
    for(auto& abilityPtr : mobAbilities)
        if (abilityPtr != nullptr)
             abilityPtr->update(timestep);


}

SceneObject *AIComponent::getCurrentTarget()
{
    return currentTarget;
}

SceneObject *AIComponent::getSelf()
{
    return MobPtr;
}

void AIComponent::Search()
{
    enemiesInfoList = MobPtr->getModel()->getEnemyTags();
    for(const auto& enemyInfo : enemiesInfoList)
    {
        list<SceneObject*>* lst = MobPtr->getParentScene()->findObjectsByTag(enemyInfo.getTag());
        if (lst == nullptr || lst->empty())
            continue;
        avaliableTargets.insert(avaliableTargets.end(), lst->begin(), lst->end());
        delete lst;
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

            int distanceSqr = MobPtr->computeDistanceSqr(target);
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
     std::cout << (MobPtr->getModel()->getName()) << std::endl;
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
           int* damage = MobPtr->getModel()->getAttackDamage();

           if (currentTarget->getDestructibleObject()->receiveDamage(damage))
           {
               avaliableTargets.remove(currentTarget);
               currentTarget = nullptr;
               std::cout << "WHY" << std::endl;

           }
           delete[] damage;

           MobPtr->getModel()->reload();
           aiMobState = AIMobStates::aiRELOAD;
       }

	}
}

void AIComponent::Reload(double timestep)
{
    if (MobPtr->getModel()->getReloadTime() > 0)
        MobPtr->getModel()->setReloadTime(MobPtr->getModel()->getReloadTime() - timestep);
	else
	{
        aiMobState = (currentTarget == nullptr)? AIMobStates::aiSELECT : AIMobStates::aiATTACK;
	}
}



void AIComponent::MovetoTile(double timestep)
{

   const static pair<int, int> emptyCell = std::make_pair<int, int>(-1, -1);
    static pair<int, int> nextCell = emptyCell;
    if (currentTarget == nullptr)
    {
        aiMobState = AIMobStates::aiSELECT;
        nextCell = emptyCell;
        return;

    }

    TileMapManager* tilemapPtr = MobPtr->getTileMapManager();

    if (tilemapPtr == nullptr)
    {
        std::cout << "tilemap is null, baby" << std::endl;
        return;
    }

    pair<int, int> mobPos = tilemapPtr->getPosFromGlobalCoords(MobPtr->getPos());
    pair<int, int> targetPos = tilemapPtr->getPosFromGlobalCoords(currentTarget->getPos());

    if (distanceInRange(mobPos, targetPos))
    {
        aiMobState = AIMobStates::aiATTACK;
        nextCell = emptyCell;

        return;
    }

    if ((MobPtr->getTag() == "Tower"))
        return;

    if ((nextCell == emptyCell)|| (nextCell == mobPos))
    {
        bool canBuildPath = tilemapPtr->waveAlgo(mobPos, targetPos);

        if (canBuildPath)
        {
            list<pair<int, int> > *path = tilemapPtr->getPath(targetPos);
            nextCell = path->back();

            delete path;
        }
        else
        {
            nextCell = emptyCell;
            aiMobState = AIMobStates::aiSELECT;
        }
    }
    else
        MoveToPos(timestep, tilemapPtr->getGlobalPosFromLocalCoords(nextCell));

}

void AIComponent::MoveToPos(double timestep, SDL_Point targetPoint)
{
    double spd = MobPtr->getModel()->getMoveSpeed().first * timestep*0.002;

    int diffX =  MobPtr->getX() +static_cast<int>((targetPoint.x - MobPtr->getX())*spd);
    int diffY = MobPtr->getY()+ static_cast<int>((targetPoint.y  - MobPtr->getY())*spd);

    MobPtr->setPos(diffX, diffY);
}


bool AIComponent::distanceInRange(const pair<int, int> &firstPoint, const pair<int, int> &secondPoint)
{
    int diffX = secondPoint.first - firstPoint.first;
    int diffY = secondPoint.second - firstPoint.second;
    int current_distance = diffX*diffX + diffY*diffY;
    int attackDistance = MobPtr->getModel()->getAttackDistance().first;

    return current_distance <= attackDistance;
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


bool AIComponent::Cast(SceneObject* target)
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

    list<string> mobAbilitiesNames =  MobPtr->getModel()->getAbilitiesNames();

    for(auto ptr = mobAbilitiesNames.begin(); ptr != mobAbilitiesNames.end(); ++ptr)
    {

        mobAbilities.push_back(GameModel::getInstance()->getMobAbilityByName(*ptr));
        mobAbilities.back()->setWorkTime(4000);
        mobAbilities.back()->setCooldownTime(4000);
    }
}


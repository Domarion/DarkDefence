/*
 * AIComponent.cpp
 *
 *  Created on: 8 марта 2016 г.
 *      Author: kostya_hm
 */

#include "AIComponent.h"
#include "../GlobalScripts/GameModel.h"

AIComponent::AIComponent(MobModel* aMob, CTexture* aView, Scene* const sceneptr)
:MobPtr(aMob), SpritePtr(aView), aiMobState(AIMobStates::aiSEARCH), currentTarget(nullptr), scenePtr(sceneptr)
{
	// TODO Auto-generated constructor stub

}

AIComponent::~AIComponent()
{
	// TODO Auto-generated destructor stub
}

void AIComponent::setSprite(CTexture* aView)
{
	SpritePtr = aView;

}

void AIComponent::setScene(Scene * const sceneptr)
{
    scenePtr = sceneptr;
}

void AIComponent::MakeDecision(double timestep)
{
	switch(aiMobState)
	{
		case aiSEARCH:
			Search();
			break;
		case aiSELECT:
			Select();
			break;
		case aiMOVE:
            Move(timestep);
			break;
		case aiATTACK:
			Attack();
			break;
		case aiRELOAD:
			Reload(timestep);
			break;

		default:
			break;
    }
    for(auto abilityPtr = mobAbilities.begin(); abilityPtr != mobAbilities.end(); ++abilityPtr)
    {
        if ((*abilityPtr) != nullptr)
        {
             (*abilityPtr)->update(timestep);
        }
    }
}

DestructibleObject *AIComponent::getCurrentTarget()
{
    return currentTarget;
}

void AIComponent::Search()
{
    list<string> enemyTags = MobPtr->getEnemyTags();
    for(auto t = enemyTags.begin(); t != enemyTags.end(); ++t)
    {
        list<SceneObject*> lst = scenePtr->findObjectsByTag(*t);
        if (lst.size() == 0)
            continue;
        for (auto ptr = lst.begin(); ptr != lst.end(); ++ptr)
        {
           DestructibleObject *obj = (*ptr)->getDestructibleObject();
           if (obj != nullptr)
           {
                avaliableTargets.push_back(obj);
           }
        }



    }

    if (MobPtr->getTag() == "Monster")
    {
        std::cout << "Targets Count = " << avaliableTargets.size() << std::endl;
    }
    if (!avaliableTargets.empty())
     aiMobState = AIMobStates::aiSELECT;

}

void AIComponent::Select()
{
	if (!avaliableTargets.empty())
	{

		int closestDistanceSqr = 0;

		for(auto t = avaliableTargets.begin(); t != avaliableTargets.end(); ++t)
		{
			int distanceSqr = computeDistanceSqr(*t, MobPtr);

			if (closestDistanceSqr == 0 || distanceSqr < closestDistanceSqr)
			{
				closestDistanceSqr = distanceSqr;
				currentTarget = *t;
			}
		}
	}

	if (currentTarget == nullptr)
		aiMobState = AIMobStates::aiSEARCH;
	else
		aiMobState = AIMobStates::aiMOVE;
}

void AIComponent::Move(double timestep)
{
	if (currentTarget == nullptr)
		aiMobState = AIMobStates::aiSELECT;
	else
	{
		int distanceSqr = computeDistanceSqr(currentTarget, MobPtr);
     //   std::cout << distanceSqr << std::endl;
        if (MobPtr->checkDistance(distanceSqr))
            aiMobState = AIMobStates::aiATTACK;
        else
            MoveIt(timestep);

	}
}

void AIComponent::Attack()
{
     std::cout << (MobPtr->getName()) << std::endl;
    if (currentTarget == nullptr)
		aiMobState = AIMobStates::aiSELECT;
	else
	{

        Cast();




        int* damage = MobPtr->getAttackDamage();

        if (currentTarget->receiveDamage(damage))
        {
            avaliableTargets.remove(currentTarget);
            currentTarget = nullptr;

        }
        delete[] damage;

		MobPtr->reload();
		aiMobState = AIMobStates::aiRELOAD;

	}
}

void AIComponent::Reload(double timestep)
{
	if (MobPtr->getReloadTime() > 0)
        MobPtr->setReloadTime(MobPtr->getReloadTime() - timestep);
	else
	{
        if (currentTarget == nullptr)
		{
            aiMobState = AIMobStates::aiSELECT;
		}
		else
            aiMobState = AIMobStates::aiATTACK;
	}
}

void AIComponent::MoveIt(double timestep)
{
 //   MobPtr->setWorldX(MobPtr->getMoveSpeed().first);
  //  MobPtr->setWorldY();
    //if (MobPtr->getTag() != "Tower")
      //  std::cout << (MobPtr->getName()) << '\t' << (MobPtr->getMoveSpeed().first) << std::endl;
    if (MobPtr->getMoveSpeed().first > 0.01)
    {
        double spd = MobPtr->getMoveSpeed().first * timestep*0.0006;
        // std::cout << (MobPtr->getName()) << '\t' << (currentTarget->getWorldX() - MobPtr->getWorldX()) << std::endl;
        int diffX =  MobPtr->getWorldX() +static_cast<int>((currentTarget->getWorldX() - MobPtr->getWorldX())*spd);
        int diffY = MobPtr->getWorldY()+ static_cast<int>((currentTarget->getWorldY()  - MobPtr->getWorldY())*spd);
        MobPtr->setWorldX(diffX );
        MobPtr->setWorldY( diffY);
         int dist = computeDistanceSqr(currentTarget, MobPtr);
        std::cout << (MobPtr->getName()) << " distance = " << dist << " attackDistance = " << (MobPtr->getAttackDistance().first) << " canAttack = " << (MobPtr->checkDistance(dist)) <<std::endl ;
    }
}

int AIComponent::computeDistanceSqr(DestructibleObject* first,
	DestructibleObject* second)
{
    if (first == nullptr || second == nullptr)
       return 0;
	int xdist = first->getWorldX() - second->getWorldX();
	int ydist = first->getWorldY() - second->getWorldY();
    return (xdist*xdist + ydist*ydist);
}

bool AIComponent::Cast()
{
      std::cout << (MobPtr->getName()) << " mobAbilities size = "<< mobAbilities.size() << std::endl;
    for(auto abilityPtr = mobAbilities.begin(); abilityPtr != mobAbilities.end(); ++abilityPtr)
    {
        if ((*abilityPtr) != nullptr && (*abilityPtr)->isInProcess() == false)
        {


            if ((*abilityPtr)->isTargetable())
            {
                  std::cout << "current TARGET111" << std::endl;
                if (currentTarget == nullptr)
                    std::cout << "current TARGETNULL" << std::endl;
                (*abilityPtr)->setTarget(currentTarget);
            }

            MobAbility *temp = *abilityPtr;
            temp->setAsReady();

            std::cout << "casted?" << std::endl;

            return true;
        }
        else
           if( (*abilityPtr) == nullptr)
        std::cout << "(*abilityPtr) is NULL" << std::endl;
    }

    return false;
}

void AIComponent::initMobAbilities()
{

    list<string> mobAbilitiesNames =  MobPtr->getAbilitiesNames();
    std::cout << "MobName = " << MobPtr->getName() << " INITMOBABS size = " << mobAbilitiesNames.size() << std::endl;

    for(auto ptr = mobAbilitiesNames.begin(); ptr != mobAbilitiesNames.end(); ++ptr)
    {

        mobAbilities.push_back(GameModel::getInstance()->getMobAbilityByName(*ptr));
        if (*ptr != "MobAbilityArson")
            mobAbilities.back()->setTarget(MobPtr);

        mobAbilities.back()->setWorkTime(4000);
         mobAbilities.back()->setCooldownTime(4000);
        std::cout << (*ptr) << std::endl;
    }
}

/*
 * AIComponent.cpp
 *
 *  Created on: 8 марта 2016 г.
 *      Author: kostya_hm
 */

#include "AIComponent.h"
#include "../GlobalScripts/GameModel.h"
/*
AIComponent::AIComponent(Mob* aMob, CTexture* aView);
:MobPtr(aMob), SpritePtr(aView), aiMobState(AIMobStates::aiSEARCH), currentTarget(nullptr)
{
	// TODO Auto-generated constructor stub

}*/

AIComponent::~AIComponent()
{
	// TODO Auto-generated destructor stub
}

AIComponent::AIComponent(Mob *aMob)
:MobPtr(aMob), aiMobState(AIMobStates::aiSEARCH), currentTarget(nullptr)

{

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
    /*for(auto abilityPtr = mobAbilities.begin(); abilityPtr != mobAbilities.end(); ++abilityPtr)
    {
        if ((*abilityPtr) != nullptr)
        {
             (*abilityPtr)->update(timestep);
        }
    }*/
}

SceneObject *AIComponent::getCurrentTarget()
{
    return currentTarget;
}

void AIComponent::Search()
{
    list<string> enemyTags = MobPtr->getModel()->getEnemyTags();
    for(auto t = enemyTags.begin(); t != enemyTags.end(); ++t)
    {
        list<SceneObject*> lst = MobPtr->getParentScene()->findObjectsByTag(*t);
        if (lst.size() == 0)
            continue;
        avaliableTargets.insert(avaliableTargets.end(), lst.begin(), lst.end());
    }

   /* if (MobPtr->getTag() == "Monster")
    {
        std::cout << "Targets Count = " << avaliableTargets.size() << std::endl;
    }*/
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


            int distanceSqr = MobPtr->computeDistanceSqr(*t);

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
        int distanceSqr = MobPtr->computeDistanceSqr(currentTarget);
        std::cout << distanceSqr << std::endl;
        if (MobPtr->getModel()->checkDistance(distanceSqr))
            aiMobState = AIMobStates::aiATTACK;
        else
            MoveIt(timestep);

	}
}

void AIComponent::Attack()
{
     std::cout << (MobPtr->getModel()->getName()) << std::endl;
    if (currentTarget == nullptr)
		aiMobState = AIMobStates::aiSELECT;
	else
	{

       // Cast();

        int* damage = MobPtr->getModel()->getAttackDamage();

        if (currentTarget->getDestructibleObject()->receiveDamage(damage))
        {
            avaliableTargets.remove(currentTarget);
            currentTarget = nullptr;

        }
        delete[] damage;

        MobPtr->getModel()->reload();
		aiMobState = AIMobStates::aiRELOAD;

	}
}

void AIComponent::Reload(double timestep)
{
    if (MobPtr->getModel()->getReloadTime() > 0)
        MobPtr->getModel()->setReloadTime(MobPtr->getModel()->getReloadTime() - timestep);
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
    if (MobPtr->getTag() != "Tower")
        std::cout << (MobPtr->getModel()->getName()) << '\t' << (MobPtr->getModel()->getMoveSpeed().first) << std::endl;
   double mspd = MobPtr->getModel()->getMoveSpeed().first;
    if (mspd > 0.01)
    {
        double spd = mspd * timestep*0.002;
        // std::cout << (MobPtr->getName()) << '\t' << (currentTarget->getWorldX() - MobPtr->getWorldX()) << std::endl;
        int diffX =  MobPtr->getX() +static_cast<int>((currentTarget->getX() - MobPtr->getX())*spd);
        int diffY = MobPtr->getY()+ static_cast<int>((currentTarget->getY()  - MobPtr->getY())*spd);
        MobPtr->setX(diffX );
        MobPtr->setY( diffY);
         int dist = MobPtr->computeDistanceSqr(currentTarget);
        std::cout << (MobPtr->getModel()->getName())
                  << " distance = " << dist
                  << " attackDistance = " << (MobPtr->getModel()->getAttackDistance().first)
                  << " canAttack = " << (MobPtr->getModel()->checkDistance(dist)) << std::endl;
    }
}


/*bool AIComponent::Cast()
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
*/

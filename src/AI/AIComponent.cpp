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
            MovetoTile(timestep);
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
        list<SceneObject*>* lst = MobPtr->getParentScene()->findObjectsByTag(*t);
        if (lst == nullptr || lst->size() == 0)
            continue;
        avaliableTargets.insert(avaliableTargets.end(), lst->begin(), lst->end());
        delete lst;
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

/*void AIComponent::Move(double timestep)
{
    static pair<int, int> nextCell = std::make_pair<int, int>(-1, -1);
	if (currentTarget == nullptr)
    {
		aiMobState = AIMobStates::aiSELECT;
        nextCell.first = -1;
        nextCell.second = -1;
    }
	else
	{


        int distanceSqr = MobPtr->computeDistanceSqr(currentTarget);
        std::cout << distanceSqr << std::endl;
        if (MobPtr->getModel()->checkDistance(distanceSqr))
            aiMobState = AIMobStates::aiATTACK;
        else
            MoveIt(timestep);
        if (MobPtr->getModel()->getMoveSpeed().first < 1e-3)
            return;

        TileMapManager* tilemapPtr = MobPtr->getTileMapManager();
        if (tilemapPtr == nullptr)
        {
           std::cout << "tilemap is null, baby" << std::endl;
           return;
        }
        SDL_Point mobPos = tilemapPtr->getPosFromGlobalCoords(MobPtr->getX(), MobPtr->getY());
         std::cout << "MobPosGX = " << (MobPtr->getX()) << " MobPosGY = " << (MobPtr->getY()) << std::endl;
        std::cout << "MobPosX = " << mobPos.x << " MobPosY = " << mobPos.y << std::endl;
        SDL_Point targetPos = tilemapPtr->getPosFromGlobalCoords(currentTarget->getX(), currentTarget->getY());
        std::cout << "TGPosX = " << (currentTarget->getX()) << " TGPosY = " << (currentTarget->getY()) << std::endl;
           std::cout << "TPosX = " << targetPos.x << " TPosY = " << targetPos.y << std::endl;
        if (abs(mobPos.x - targetPos.x) <= 1 && abs(mobPos.y - targetPos.y) <= 1)
              aiMobState = AIMobStates::aiATTACK;
        else
        {
            const double EPSem3 = 1e-3;
            if (MobPtr->getModel()->getMoveSpeed().first > EPSem3 &&
                    (nextCell.first == -1 || (nextCell.first == mobPos.x && nextCell.second == mobPos.y)))
            {

                //std::cout << "can move!" << std::endl;
                pair<int, int> endVertex =  {targetPos.x, targetPos.y};
                bool canBuildPath = tilemapPtr->waveAlgo(std::make_pair(mobPos.x, mobPos.y),
                                     endVertex);

                if (canBuildPath)
                {
                    std::cout << "can move!" << std::endl;
                    list<pair<int, int> > *path = tilemapPtr->getPath(endVertex);
                    nextCell = path->back();

                    delete path;

                }
                else
                {
                    nextCell.first = -1;
                    nextCell.second = -1;
                   aiMobState = AIMobStates::aiSELECT;
                }
            }
            else
                if (nextCell.first >= 0 && nextCell.second >= 0)
                {
                    std::cout << "i'm herer nextCell >0" << std::endl;

                    SDL_Point nextCellGlobalPos = tilemapPtr->getGlobalPosFromLocalCoords(nextCell.first, nextCell.second);



                    double spd = MobPtr->getModel()->getMoveSpeed().first * timestep*0.002;
                    // std::cout << (MobPtr->getName()) << '\t' << (currentTarget->getWorldX() - MobPtr->getWorldX()) << std::endl;
                    int diffX =  MobPtr->getX() +static_cast<int>((nextCellGlobalPos.x - MobPtr->getX())*spd);
                    int diffY = MobPtr->getY()+ static_cast<int>((nextCellGlobalPos.y  - MobPtr->getY())*spd);
                    MobPtr->setX(diffX );
                    MobPtr->setY( diffY);
                    // int dist = MobPtr->computeDistanceSqr(currentTarget);



                }
        }

	}
}*/

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

/*void AIComponent::MoveIt(double timestep)
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
*/

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

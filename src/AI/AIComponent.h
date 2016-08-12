/*
 * AIComponent.h
 *
 *  Created on: 8 марта 2016 г.
 *      Author: kostya_hm
 */

#pragma once

#include "../Mob/Mob.h"
#include <list>
using std::list;
#include <SDL_rect.h>
#include <utility>
using std::pair;

//#include "../AbilitySystem/MobAbilities/MobAbility.h"
class Mob;
class SceneObject;

class AIComponent
{
public:
    AIComponent(Mob* aMob = nullptr);
    virtual ~AIComponent();
	virtual void MakeDecision(double timestep);
    SceneObject* getCurrentTarget();

   // void initMobAbilities();
protected:
    Mob* MobPtr;

	enum AIMobStates{aiSEARCH = 0, aiSELECT, aiMOVE, aiATTACK, aiRELOAD} aiMobState;
    SceneObject* currentTarget;
    list<SceneObject*> avaliableTargets;
    //list<MobAbility*> mobAbilities;
private:
	void Search();
	void Select();
    //void Move(double timestep);
    void Attack();
	void Reload(double timestep);
    //void MoveIt(double timestep);
    void MovetoTile(double timestep);

    void MoveToPos(double timestep, SDL_Point targetPoint);
    //bool Cast();

    bool distanceInRange(const pair<int, int>& firstPoint, const pair<int, int>& secondPoint);


};



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
#include "../Enums.h"
using Enums::AIMobStates;
#include "../AbilitySystem/MobAbilities/MobAbility.h"
class Mob;
class EnemyInfo;
class SceneObject;

#include <string>
using std::string;

class AIComponent
{
public:
    AIComponent(Mob* aMob = nullptr);
    virtual ~AIComponent();
	virtual void MakeDecision(double timestep);
    SceneObject* getCurrentTarget();
    SceneObject* getSelf();
    void initMobAbilities();
protected:
    Mob* MobPtr;

    AIMobStates aiMobState;
    SceneObject* currentTarget;
    list<SceneObject*> avaliableTargets;
    list<EnemyInfo> enemiesInfoList;
    list<MobAbility*> mobAbilities;
private:
	void Search();
	void Select();
    void Attack();
	void Reload(double timestep);
    void MovetoTile(double timestep);

    void MoveToPos(double timestep, SDL_Point targetPoint);
    bool Cast(SceneObject* target);

    bool distanceInRange(const pair<int, int>& firstPoint, const pair<int, int>& secondPoint);
    int getPriorityFromTag(const string& aTag);
    Enums::EReaction getReactionByTag(const string& aTag);

};



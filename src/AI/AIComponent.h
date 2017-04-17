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
    AIComponent(std::weak_ptr<Mob> aMob);
    virtual ~AIComponent() = default;
	virtual void MakeDecision(double timestep);
    std::shared_ptr<SceneObject> getCurrentTarget();
    void initMobAbilities();
protected:
    std::weak_ptr<Mob> MobPtr;

    AIMobStates aiMobState;
    std::shared_ptr<SceneObject> currentTarget;
    list<std::shared_ptr<SceneObject>> avaliableTargets;
    list<EnemyInfo> enemiesInfoList;
    list<std::shared_ptr<MobAbility>> mobAbilities;
private:
	void Search();
	void Select();
    void Attack();
	void Reload(double timestep);
    void MovetoTile(double timestep);

    void MoveToPos(double timestep, Position targetPoint);
    bool Cast(std::shared_ptr<SceneObject> target);

    bool distanceInRange(const pair<int, int>& firstPoint, const pair<int, int>& secondPoint);
    int signum(int aValue) const;
    int getPriorityFromTag(const string& aTag);
    Enums::EReaction getReactionByTag(const string& aTag);
    pair<int, int> currentTargetPosition;
    std::unique_ptr<std::list<std::pair<int, int>>> currentPath;
    std::pair<int, int> nextCell;
};



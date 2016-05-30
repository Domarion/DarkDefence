/*
 * AIComponent.h
 *
 *  Created on: 8 марта 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include "../Mob/MobModel.h"
#include "../GraphicsSystem/CTexture.h"
#include <list>
using std::list;
#include "../Mob/DestructibleObject.h"

#include "../Grouping/Scene.h"
#include "../AbilitySystem/MobAbilities/MobAbility.h"

class AIComponent
{
public:
    AIComponent(MobModel* aMob = nullptr, CTexture* aView = nullptr, Scene* const sceneptr = nullptr);
    void setSprite(CTexture* aView);
    void setScene(Scene* const sceneptr);
	virtual ~AIComponent();
	virtual void MakeDecision(double timestep);
    DestructibleObject* getCurrentTarget();
    void initMobAbilities();
protected:
	MobModel* MobPtr;
    CTexture* SpritePtr;
	enum AIMobStates{aiSEARCH = 0, aiSELECT, aiMOVE, aiATTACK, aiRELOAD} aiMobState;
	DestructibleObject* currentTarget;
	list<DestructibleObject*> avaliableTargets;
    Scene* scenePtr;
    list<MobAbility*> mobAbilities;
private:
	void Search();
	void Select();
    void Move(double timestep);
    void Attack();
	void Reload(double timestep);
    void MoveIt(double timestep);
	int computeDistanceSqr(DestructibleObject* first, DestructibleObject* second);
    bool Cast();


};



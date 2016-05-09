/*
 * AIComponent.h
 *
 *  Created on: 8 марта 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include "../Mob/MobModel.h"
#include "../GraphicsSystem/Sprite.h"
#include <list>
using std::list;
#include "../Mob/DestructibleObject.h"

#include "../Grouping/Scene.h"
class MobModel;

class AIComponent
{
public:
    AIComponent(MobModel* aMob = nullptr, Sprite* aView = nullptr, Scene* const sceneptr = nullptr);
	void setSprite(Sprite* aView);
    void setScene(Scene* const sceneptr);
	virtual ~AIComponent();
	virtual void MakeDecision(double timestep);
    DestructibleObject* getCurrentTarget();
protected:
	MobModel* MobPtr;
	Sprite* SpritePtr;
	enum AIMobStates{aiSEARCH = 0, aiSELECT, aiMOVE, aiATTACK, aiRELOAD} aiMobState;
	DestructibleObject* currentTarget;
	list<DestructibleObject*> avaliableTargets;
    Scene* scenePtr;
private:
	void Search();
	void Select();
    void Move(double timestep);
	void Attack();
	void Reload(double timestep);
    void MoveIt(double timestep);
	int computeDistanceSqr(DestructibleObject* first, DestructibleObject* second);
};



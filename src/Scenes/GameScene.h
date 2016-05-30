/*
 * GameScene.h
 *
 *  Created on: 4 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include "../Grouping/Scene.h"
#include "../Mob/MobSpawner.h"
#include "../Grouping/SceneObjectFabric.h"
#include "../GraphicsSystem/UI/AnimatedSprite.h"
#include "../GraphicsSystem/UI/GroupBox.h"
#include "../GraphicsSystem/UI/CompositeLabel.h"
//#include "../GraphicsSystem/UI/TextButton.h"
#include "../GraphicsSystem/UI/ImageButton.h"
#include "../GraphicsSystem/UI/ProgressBar.h"


#include "../Mob/Gates.h"

#include "../MissionSystem/Mission.h"
#include <vector>
using std::vector;
#include "../AbilitySystem/AbilityMagicStones.h"
#include "../AbilitySystem/AbilitySnowStorm.h"
#include "../AbilitySystem/AbilityShrink.h"
#include "../AbilitySystem/AbilityPrick.h"
#include "../Mob/ResourcePlace.h"
#include "../Mob/TowerFabric.hpp"
#include "../Mob/TowerUpgradeController.h"

class GameScene: public Scene
{
public:
	GameScene();
	virtual ~GameScene();
    virtual void initScene(SceneManager* sceneManagerPtr) override;
	virtual void finalizeScene() override;
	virtual void startUpdate(double timestep) override;
    virtual void copyToRender() const override;
    AbilityModel* getAbilityModelWithName(string name);
    map<string, AbilityModel* >& getAbilityModelList();
private:
    SceneObjectFabric objectFabric;
    SceneObject* Terrain;
    vector<ImageButton> abilityButtons;
    GroupBox topPanel;
    vector<CompositeLabel*> resourceLabels;
    ProgressBar gatesHealthBar;

    ProgressBar manaBar;
    TowerFabric towerFabric;
	MobSpawner monsterSpawner;
	Gates gates;
    //SDL_Rect* worldRect;

    Mission currentMission;
    std::shared_ptr<CFont> arialFont;
    Label pointsLabel;
    Label waveLabel;
    map<string, AbilityModel* > abilityModelsMap;


    ResourcePlace *resPlace;
    TowerUpgradeController towerUpgradeController;
  //  AbilityMagicStones magicStones;
   // AbilitySnowStorm snowStorm;
    void setActiveMstones(string s);
};

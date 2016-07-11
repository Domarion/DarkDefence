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
#include "../AbilitySystem/SpellStorage.h"

#include "../Mob/ResourcePlace.h"
#include "../Mob/TowerFabric.hpp"
#include "../Mob/TowerUpgradeController.h"
#include "../AbilitySystem/ItemAbilities/ItemAbilitiesStorage.h"

class GameScene: public Scene
{
public:
	GameScene();
	virtual ~GameScene();
    virtual void initScene(SceneManager* sceneManagerPtr) override;

	virtual void startUpdate(double timestep) override;
    virtual void copyToRender() const override;

    map<string, AbilityModel* >& getAbilityModelList();
    void ConnectMethod(std::function<void(string)> handler);
    AbilityModel*getAbilityModelWithName(string name);
    void sendMessage(string msgText);
private:

    void loadData();
    SceneObjectFabric objectFabric;
    SceneObject* Terrain;
    vector<ImageButton> abilityButtons;
    GroupBox topPanel;
    vector<CompositeLabel*> resourceLabels;
    ProgressBar gatesHealthBar;

    ProgressBar manaBar;
    TowerFabric towerFabric;
	MobSpawner monsterSpawner;
    Gates* gates;

    Mission currentMission;
    //std::shared_ptr<CFont> arialFont;
    Label pointsLabel;
    Label waveLabel;


    SpellStorage spellStorage;
    ItemAbilitiesStorage itemAbilitiesStorage;
    ResourcePlace *resPlace;
    TowerUpgradeController towerUpgradeController;

    ImageButton pauseBtn;
    ImageButton resumeBtn;
    void setActiveMstones(string s);
    std::function<void(string)> method;
};

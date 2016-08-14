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
    virtual void init(SceneManager* sceneManagerPtr) override;
    virtual void clear() override;
	virtual void startUpdate(double timestep) override;

    map<string, AbilityModel* >& getAbilityModelList();
    void ConnectMethod(std::function<void(string)> handler);
    AbilityModel* getAbilityModelWithName(string name);
    void sendMessage(string msgText);
private:

    void loadData();

    void initTopPanel();
    void initAbilitiesButtons();
    void initUILayer();

    void placeResourcesPlaces();
    void placeCastle();
    void placeTowers();
    void placeSceneObjects();

    void applyArtefactEffects();

    Gates* gates;
    ProgressBar *gatesHealthBar, *manaBar;
    Label* pointsLabel;
    Label* waveLabel;

    vector<vector<int> > loadMapTemplate(string mapPath);
    SceneObjectFabric objectFabric;


    vector<CompositeLabel*> resourceLabels;

    TowerFabric towerFabric;
	MobSpawner monsterSpawner;


    Mission currentMission;



    SpellStorage spellStorage;
    ItemAbilitiesStorage itemAbilitiesStorage;
    TowerUpgradeController towerUpgradeController;


    void setActiveMstones(string s);
    std::function<void(string)> method;

    TileMapManager* tileMap;
};

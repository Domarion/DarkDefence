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
#include "../GraphicsSystem/newSystem/UIElement/UILabel.h"
#include "../GraphicsSystem/newSystem/UIElement/UIProgressBar.h"

#include "../Mob/Gates.h"

#include "../MissionSystem/Mission.h"
#include <vector>
using std::vector;
#include "../AbilitySystem/SpellStorage.h"

#include "../Mob/ResourcePlace.h"
#include "../Mob/TowerFabric.hpp"
#include "../Mob/TowerUpgradeController.h"
#include "../AbilitySystem/ItemAbilities/ItemAbilitiesStorage.h"

#include "../GlobalScripts/ManaGlobal.h"
#include "Utility/StructData.hpp"

class GameScene: public Scene
{
public:
    GameScene(std::shared_ptr<RenderingSystem> &aRenderer, std::shared_ptr<InputDispatcher> aInputDispatcher);
	virtual ~GameScene();
    virtual void init(std::shared_ptr<SceneManager> sceneManagerPtr) override;
    virtual void clear() override;
	virtual void startUpdate(double timestep) override;

    map<std::string, std::shared_ptr<AbilityModel> > &getAbilityModelList();
    void ConnectMethod(std::function<void(string)> handler);
    std::shared_ptr<AbilityModel> getAbilityModelWithName(string name);
    void sendMessage(string msgText);

    std::shared_ptr<ManaGlobal> getManaModel() const;
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

    std::shared_ptr<Gates> gates;
    std::shared_ptr<UIProgressBar> gatesHealthBar, manaBar;
    std::shared_ptr<UILabel> pointsLabel;
    std::shared_ptr<UILabel> waveLabel;

    SceneObjectFabric objectFabric;


    vector<std::shared_ptr<UILabel> > resourceLabels;

    TowerFabric towerFabric;
	MobSpawner monsterSpawner;


    Mission currentMission;


    SpellStorage spellStorage;
    ItemAbilitiesStorage itemAbilitiesStorage;
    std::shared_ptr<TowerUpgradeController> towerUpgradeController;


    void setActiveMstones(string s);
    std::function<void(string)> method;

    std::shared_ptr<TileMapManager> tileMap;
    std::shared_ptr<ManaGlobal> mManaModel;
    vector<StructureData> mPositionsVector;
    void initResourceView();
    void initProgressBars();
};

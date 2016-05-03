/*
 * GameModel.h
 *
 *  Created on: 14 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include "ResourcesModel.h"
#include "../Enums.h"
#include "../Mob/MobModel.h"
#include "../ItemSystem/HeroInventory.h"
#include "../ItemSystem/ShopInventory.h"
#include <map>
using std::map;
#include "../Utility/TreeNode.hpp"
#include "../MissionSystem/Mission.h"
#include <vector>
using std::vector;



class GameModel
{

public:

	static GameModel* const getInstance();
	ResourcesModel* const getResourcesModel();
	MobModel* const getMonsterByName(string name);
    MobModel* const getTowerByName(string name);
	void loadMonsterList(string filename);

	void loadTowerUpgrades(string filename);
    //void deserialize(MobModel& obj, string filename);

    void deserialize(Mission& obj, string filename);
	void loadShopItems(string filename);
	ShopInventory* getShopInventory();
	Inventory* getInventory();
	TreeNode<MobModel> * getRootTower();
	bool canSpawn() const;
	void incMonsterCount();
	void decMonsterCount();
    void setCurrentMissionIndex( int newValue);
    int getCurrentMissionIndex() const;
    Enums::GameStatuses getGameStatus() const;
    void setGameStatus(const Enums::GameStatuses &value);
    int getMonsterCount() const;

    Reward getMissionReward() const;
    void setMissionReward(const Reward &value);
    void loadAbilitiesNames(string filename);
    string getAbilityNameFromIndex(int index);
    int getAbilityCount() const;
private:
    GameModel();
    ~GameModel();

    int waveNumber, waveCount;
    int pointsPerWave, pointsPerMap, pointsRefundModifier;
	int MonsterCountOnMap;
	Enums::GameStatuses gameStatus;
    int currentMissionIndex;
	ShopInventory shop;
	HeroInventory heroFigure;
	Inventory inventory;
	ResourcesModel* resourcesModelPtr;
	map<string, MobModel> monstersModelsMap;
	TreeNode<MobModel> towerUpgradesRootNode;
    Reward missionReward;
    vector<string> abilitiesNames;

	static GameModel* instance_;
};


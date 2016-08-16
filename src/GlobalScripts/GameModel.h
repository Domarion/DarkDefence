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
#include "../Mob/MineModel.h"
#include "../ItemSystem/HeroInventory.h"
#include "../ItemSystem/ShopInventory.h"
#include <map>
using std::map;
#include "../Utility/TreeNode.hpp"
#include "../MissionSystem/Mission.h"
#include <vector>
using std::vector;

#include "ManaGlobal.h"
//#include "../AbilitySystem/ItemAbilities/ItemAbility.h"
#include "../AbilitySystem/MobAbilities/MobAbility.h"
//class ItemAbility;
class MobAbility;

class GameModel//TODO: разделение на мелкие классы
{

public:

    static GameModel* getInstance();
    ResourcesModel* getResourcesModel();
    MobModel* getMonsterByName(string name);
    MobModel* getTowerByName(string name);

	void loadMonsterList(string filename);
    void loadMonsterPointsList(string filename);
	void loadTowerUpgrades(string filename);
    void loadMinesList(string filename);
    //void deserialize(MobModel& obj, string filename);



    void deserialize(Mission& obj, string filename);
    bool loadShopItems(string filename);

	ShopInventory* getShopInventory();
	Inventory* getInventory();
    HeroInventory* getHeroInventory();
	TreeNode<MobModel> * getRootTower();


    void addItemToInventoryByName(string name);

	bool canSpawn() const;
	void incMonsterCount();
    void decMonsterCount(string monsterName);

    void setCurrentMissionIndex( int newValue);
    int getCurrentMissionIndex() const;

    Enums::GameStatuses getGameStatus() const;
    void setGameStatus(const Enums::GameStatuses &value);
    int getMonsterCount() const;


    MineModel *getMineModel(string name);
    MineModel *getMineModelByRes(Enums::ResourceTypes resType);


    MineModel *getMineModelFromList(string name);
    MineModel *getMineModelFromListByRes(Enums::ResourceTypes resType);

    MobModel* getMonsterFromListWithName(string name);
    map<string, MobModel>& getMonsterList();

    const Reward& getMissionReward() const;
    void setMissionReward(const Reward &value);

    void loadAbilitiesNames(string filename);
    string getAbilityNameFromIndex(int index);
    int getAbilityCount() const;

    void calculatePointsPerWave();
    int getPointsPerWave() const;

    void resetGameValues();
    ManaGlobal* getManaModel();
    double getPointsRefundModifier() const;
    void setPointsRefundModifier(double value);

   // void loadMobAbilities();

    MobAbility* getMobAbilityByName(string name);

    void saveGameData(string filename);
    void loadGameData(string filename);
private:
    GameModel();
    ~GameModel();

    int waveNumber, waveCount;
    int pointsPerWave, pointsPerMap;
    double pointsRefundModifier;
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
    map<string, int> monsterPointsMap;
	static GameModel* instance_;
    map<string, MineModel> minesModelsMap;

    vector<string> mineResMapping;

    ManaGlobal manaModel;


    map<string, MobAbility*> mobAbilitiesMap;
    bool shopItemsLoaded;
    bool gameDataLoaded;
};


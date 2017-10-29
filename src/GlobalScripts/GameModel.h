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
#include "../Utility/TreeNode.hpp"
#include "../MissionSystem/Mission.h"
#include <vector>

#include "ManaGlobal.h"
#include "../AbilitySystem/MobAbilities/MobAbility.h"

using std::map;
using std::vector;

class MobAbility;

class GameModel//TODO: разделение на мелкие классы
{

public:

    static GameModel* getInstance();
    const std::shared_ptr<ResourcesModel>& getResourcesModel() const;
    std::unique_ptr<MobModel> getMonsterByName(const std::string& aName);
    std::unique_ptr<MobModel> getTowerByName(const std::string& aName);

    void loadMonsterList(const std::string& aFileName);
    void loadMonsterPointsList(const std::string& aFileName);
    void loadTowerUpgrades(const std::string& aFileName);
    void loadMinesList(const std::string& aFileName);

    void deserialize(Mission& obj, const std::string& aFileName);
    bool loadShopItems(const std::string& aFileName);

    std::shared_ptr<ShopInventory> getShopInventory();
    std::shared_ptr<Inventory> getInventory();
    std::shared_ptr<HeroInventory> getHeroInventory();
    const std::shared_ptr<TreeNode<MobModel>>& getRootTower() const;


    void addItemToInventoryByName(string name);

    bool NoMonstersOnMap() const;
    void incMonsterCount();
    void decMonsterCount(string monsterName);

    void setCurrentMissionIndex( int newValue);
    int getCurrentMissionIndex() const;

    Enums::GameStatuses getGameStatus() const;
    void setGameStatus(const Enums::GameStatuses& value);
    int getMonsterCount() const;

    std::unique_ptr<MineModel> getMineModel(const std::string& aName);
    std::unique_ptr<MineModel> getMineModelByRes(Enums::ResourceTypes resType);

    MineModel* getMineModelFromList(const string& aName);
    MineModel* getMineModelFromListByRes(Enums::ResourceTypes resType);

    MobModel* getMonsterFromListWithName(const std::string& aName);
    map<string, MobModel>& getMonsterList();

    const Reward& getMissionReward() const;
    void setMissionReward(const Reward& value);

    void loadAbilitiesNames(const std::string& aFileName);
    const string& getAbilityNameFromIndex(size_t aIndex) const;
    size_t getAbilityCount() const;

    void calculatePointsPerWave();
    int getPointsPerWave() const;

    void resetGameValues();
    double getPointsRefundModifier() const;
    void setPointsRefundModifier(double value);

    void addPoints(int aAmount);

    std::unique_ptr<MobAbility> getMobAbilityByName(string name);

    void saveGameData(const std::string& aFileName);
    void loadGameData(const std::string& aFileName);
private:
    GameModel();
    ~GameModel() = default;
    static GameModel* instance_;

    int waveNumber, waveCount;
    int pointsPerWave, pointsPerMap;
    double pointsRefundModifier;
    int MonsterCountOnMap;
    Enums::GameStatuses gameStatus;
    int currentMissionIndex;
    std::shared_ptr<ShopInventory> shop;
    std::shared_ptr<HeroInventory> heroFigure;
    std::shared_ptr<Inventory> inventory;
    std::shared_ptr<ResourcesModel> resourcesModelPtr;
    map<string, MobModel> monstersModelsMap;
    std::shared_ptr<TreeNode<MobModel>> towerUpgradesRootNode;
    Reward missionReward;
    vector<string> abilitiesNames;
    map<string, int> monsterPointsMap;
    map<string, MineModel> minesModelsMap;

    vector<string> mineResMapping;

    bool shopItemsLoaded;
    bool gameDataLoaded;
};


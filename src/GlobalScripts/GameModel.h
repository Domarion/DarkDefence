#pragma once

#include <map>
#include <vector>

#include "ResourcesModel.h"
#include "../Enums.h"
#include "../Mob/MobModel.h"
#include "../Mob/MineModel.h"
#include "../ItemSystem/HeroInventory.h"
#include "../ItemSystem/ShopInventory.h"
#include "../Utility/TreeNode.hpp"
#include "../MissionSystem/Mission.h"

#include "ManaGlobal.h"
#include "../AbilitySystem/MobAbilities/MobAbility.h"

#include "../Scenes/include/MissionTumbler.hpp"

using std::map;
using std::vector;

class MobAbility;

class GameModel//TODO: разделение на мелкие классы
{

public:

    static GameModel* getInstance();
    std::shared_ptr<ResourcesModel> getResourcesModelNonConst();
    const std::shared_ptr<ResourcesModel>& getResourcesModel() const;

    std::unique_ptr<MobModel> getMonsterByName(const std::string& aName);
    std::unique_ptr<MobModel> getTowerByName(const std::string& aName);

    void loadMonsterList(const std::string& aFileName);
    void loadMonsterPointsList(const std::string& aFileName);
    void loadTowerUpgrades(const std::string& aFileName);
    void loadMinesList(const std::string& aFileName);

    bool loadShopItems(const std::string& aFileName);

    const std::shared_ptr<ShopInventory>& getShopInventory() const;
    const std::shared_ptr<Inventory>& getInventory() const;
    const std::shared_ptr<HeroInventory>& getHeroInventory() const;
    const std::shared_ptr<TreeNode<MobModel>>& getRootTower() const;


    void addItemToInventoryByName(const std::string& aItemName);

    bool NoMonstersOnMap() const;
    void incMonsterCount();
    void decMonsterCount(const std::string& aMonsterName);

    Enums::GameStatuses getGameStatus() const;
    void setGameStatus(Enums::GameStatuses aGameStatus);
    int getMonsterCount() const;

    std::unique_ptr<MineModel> getMineModel(const std::string& aName);
    std::unique_ptr<MineModel> getMineModelByRes(Enums::ResourceTypes aResType);

    MineModel* getMineModelFromList(const string& aName);
    MineModel* getMineModelFromListByRes(Enums::ResourceTypes aResType);

    MobModel* getMonsterFromListWithName(const std::string& aName);
    map<string, MobModel>& getMonsterList();

    const Reward& getMissionReward() const;
    void setMissionReward(const Reward& value);

    void loadAbilitiesNames(const std::string& aFileName);
    const string& getAbilityNameFromIndex(size_t aIndex) const;
    size_t getAbilityCount() const;

    void calculatePointsPerWave();
    int getPointsPerWave() const;

    void loadMissions(const std::string& aPath);

    void resetGameValues();
    double getPointsRefundModifier() const;
    void setPointsRefundModifier(double aPointsModifier);

    void addPoints(int aAmount);

    std::unique_ptr<MobAbility> getMobAbilityByName(const std::string& aName) const;

    void saveGameData(const std::string& aFileName);
    void loadGameData(const std::string& aFileName);

    MissionTumbler& getMissionSwitcher();

    void receiveShopItem(ItemModel aItem);
    void receiveInventoryItem(ItemModel aItem);
    void receiveHeroFigureItem(ItemModel aItem);


private:
    GameModel();
    ~GameModel() = default;
    static GameModel* instance_;

    int waveNumber = 0, waveCount = 0;
    int pointsPerWave = 0, pointsPerMap = 0;
    double pointsRefundModifier = 1;
    int MonsterCountOnMap = 0;
    Enums::GameStatuses gameStatus = Enums::GameStatuses::gsINPROGRESS;
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

    bool shopItemsLoaded = false;
    bool gameDataLoaded = false;
    MissionTumbler mMissionsSwitcher;
};


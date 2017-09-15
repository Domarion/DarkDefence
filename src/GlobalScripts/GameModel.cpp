/*
 * GameModel.cpp
 *
 *  Created on: 14 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "GameModel.h"
#include <fstream>
#include <list>

#include <iostream>
#include <functional>
#include "../MissionSystem/ResourceGoal.h"

#include "../AbilitySystem/MobAbilities/MobAbilityArson.h"
#include "../AbilitySystem/MobAbilities/MobAbilityRegeneration.h"
#include "../AbilitySystem/MobAbilities/MobAbilitySprint.h"
#include "../AbilitySystem/MobAbilities/MobAbilityInvisiblity.h"
#include "../AbilitySystem/MobAbilities/MobAbilityFog.h"
#include "../AbilitySystem/MobAbilities/MobAbilitySummon.h"
#include "../AbilitySystem/MobAbilities/MobAbilityInvulnerablity.h"
#include "../AbilitySystem/MobAbilities/MobAbilityHeal.h"

#include "../AbilitySystem/MobAbilities/MobAbilityWheat.h"
#include "../AbilitySystem/MobAbilities/GulakiUpgrade.h"
#include "../AbilitySystem/MobAbilities/MobEarthTowerAbility.h"
#include "../AbilitySystem/MobAbilities/MobMageTowerAbility.h"
#include "../AbilitySystem/MobAbilities/MobCloudTowerAbility.h"
#include "../AbilitySystem/MobAbilities/TitanChockUpgrade.h"
#include "../AbilitySystem/MobAbilities/TitanChockMassSlow.h"

#include "../Utility/textfilefunctions.h"
#include <sstream>
#include "AccountModel.h"

#include <cereal/archives/xml.hpp>
#include <cereal/types/memory.hpp>
#include "../Logging/Logger.h"

using std::list;
using std::ifstream;
using std::stringstream;

GameModel* GameModel::instance_ = nullptr;

GameModel::GameModel()
    : waveNumber(0)
    , waveCount(0)
    , pointsPerWave(0)
    , pointsPerMap(0)
    , pointsRefundModifier(1)
    , MonsterCountOnMap( 0 )
    , gameStatus(Enums::GameStatuses::gsINPROGRESS)
    , currentMissionIndex(0)
    , shop(std::make_shared<ShopInventory>())
    , heroFigure(std::make_shared<HeroInventory>(9))
    , inventory(std::make_shared<Inventory>())
    , resourcesModelPtr(std::make_shared<ResourcesModel>())
    , towerUpgradesRootNode(std::make_shared<TreeNode<MobModel>>())
    , missionReward()
    , shopItemsLoaded(false)
    , gameDataLoaded(false)
{
}

std::unique_ptr<MobModel> GameModel::getMonsterByName(const std::string& aName)
{
    return std::make_unique<MobModel>(monstersModelsMap[aName]);
}

std::unique_ptr<MobModel> GameModel::getTowerByName(const std::string& aName)
{
    auto temp = towerUpgradesRootNode->recursiveSearch(aName);

    if (!temp)
        return nullptr;

    return std::make_unique<MobModel>(*temp->getData());
}

void GameModel::loadMonsterList(const std::string& aFileName)
{
    list<MobModel> monsterCollection;

    string textString;
    androidText::loadTextFileToString(aFileName, textString);

    if (!textString.empty())
    {
        stringstream str(textString);

        cereal::XMLInputArchive xmlinp(str);

        LOG_INFO("Loading Monster List.");
        xmlinp(cereal::make_nvp("Monsters", monsterCollection));
    }

    auto beginMove = std::make_move_iterator(monsterCollection.begin());
    auto endMove =std::make_move_iterator(monsterCollection.end());
    for(auto i = beginMove ; i != endMove; ++i)
    {
        monstersModelsMap.emplace(i->getName(), *i);
    }
}

void GameModel::loadMonsterPointsList(const std::string& aFileName)
{
    string textString;
    androidText::loadTextFileToString(aFileName, textString);

    if (!textString.empty())
    {
        stringstream pointStream(textString);

        int n;
        pointStream >> n;

        LOG_INFO("Loading Monster Points.");

        for(int i = 0; i < n; ++i)
        {
            string str;
            int val;
            pointStream >> str >> val;
            monsterPointsMap[str] =  val;
        }
    }
}

void GameModel::loadTowerUpgrades(const std::string& aFileName)
{
    string textString;
    androidText::loadTextFileToString(aFileName, textString);

    if (!textString.empty())
    {
        try
        {
            stringstream str(textString);

            LOG_INFO("Loading Tower Upgrades.");

            cereal::XMLInputArchive xmlinp(str);
            xmlinp(cereal::make_nvp("TowerTree", towerUpgradesRootNode));
        }
        catch(const std::exception& ex)
        {
            std::string msg = std::string{"Can't load Tower Upgrades from file: "} + std::string{ex.what()};
            LOG_ERROR(msg);
        }
    }
}

void GameModel::loadMinesList(const std::string& aFileName)
{
    list<MineModel> mineCollection;

    string textString;
    androidText::loadTextFileToString(aFileName, textString);

    if (!textString.empty())
    {
        stringstream str(textString);

        cereal::XMLInputArchive xmlinp(str);

        LOG_INFO("Loading Mines List.");

        xmlinp(cereal::make_nvp("Mines", mineCollection));

        mineResMapping.resize(mineCollection.size());
    }

    for(auto i = mineCollection.begin(); i != mineCollection.end(); ++i)
    {
        mineResMapping[i->getProductionTypeIndex()] = i->getName();
        minesModelsMap.emplace(i->getName(), std::move(*i));
    }
}

void GameModel::deserialize(Mission& obj, const std::string& aFileName)
{
    string textString;
    androidText::loadTextFileToString(aFileName, textString);

    if (!textString.empty())
    {
        stringstream missionStream(textString);

        cereal::XMLInputArchive xmlinp(missionStream);
        LOG_INFO("Loading Mission Info.");

        xmlinp >> cereal::make_nvp("Mission", obj);
    }
}

std::shared_ptr<TreeNode<MobModel>> GameModel::getRootTower()
{
    return towerUpgradesRootNode;
}

void GameModel::addItemToInventoryByName(string name)
{
    shop->sendItemWithoutPriceCheck(name);
}

bool GameModel::NoMonstersOnMap() const
{
    return (MonsterCountOnMap == 0);
}

void GameModel::incMonsterCount()
{
    ++MonsterCountOnMap;
}

void GameModel::decMonsterCount(string monsterName)
{
    pointsPerWave += monsterPointsMap[monsterName];
    --MonsterCountOnMap;
}

void GameModel::setCurrentMissionIndex(int newValue)
{
    currentMissionIndex = newValue;
}

int GameModel::getCurrentMissionIndex() const
{
    return currentMissionIndex;
}

Enums::GameStatuses GameModel::getGameStatus() const
{
    return gameStatus;
}

double GameModel::getPointsRefundModifier() const
{
    return pointsRefundModifier;
}

void GameModel::setPointsRefundModifier(double value)
{
    pointsRefundModifier = value;
}

void GameModel::addPoints(int aAmount)
{
    pointsPerMap += aAmount;
}

std::unique_ptr<MobAbility> GameModel::getMobAbilityByName(string name)
{
    if (name == "MobAbilityArson")
        return std::make_unique<MobAbilityArson>();

    if (name == "MobAbilityRegeneration")
        return std::make_unique<MobAbilityRegeneration>();

    if (name == "MobAbilityHeal")
        return std::make_unique<MobAbilityHeal>();

    if (name == "MobAbilitySprint")
        return std::make_unique<MobAbilitySprint>();

    if (name == "MobAbilityFog")
        return std::make_unique<MobAbilityFog>();

    if (name == "MobAbilityInvisiblity")
        return std::make_unique<MobAbilityInvisiblity>();

    if (name == "MobAbilityInvulnerablity")
        return std::make_unique<MobAbilityInvulnerablity>();

    if (name == "MobAbilityWheat")
        return std::make_unique<MobAbilityWheat>();

    if (name == "GulakiAmulet")
        return std::make_unique<GulakiUpgrade>();

    if (name == "MobEarthTowerAbility")
        return std::make_unique<MobEarthTowerAbility>();

    if (name == "MobMageTowerAbility")
        return std::make_unique<MobMageTowerAbility>();

    if (name == "MobCloudTowerAbility")
        return std::make_unique<MobCloudTowerAbility>();

    if (name == "TitanChockUpgrade")
        return std::make_unique<TitanChockUpgrade>();

    if (name == "TitanChockMassSlow")
        return std::make_unique<TitanChockMassSlow>();

    if (name == "MobAbilitySummon")
        return std::make_unique<MobAbilitySummon>();

    return nullptr;
}

void GameModel::saveGameData(const std::string& aFileName)
{
#ifdef __ANDROID__
    string filename1(SDL_GetPrefPath("darkdefence", "game"));
    filename1.append("save.bin");
#else
    string filename1(aFileName);
#endif

    SDL_RWops* binaryDataFile = SDL_RWFromFile(filename1.c_str(),"w+b");
    if (binaryDataFile != nullptr)
    {
        int goldAmount = AccountModel::getInstance()->getGoldAmount();
        SDL_RWwrite(binaryDataFile, &goldAmount, sizeof(int), 1);
        SDL_RWwrite(binaryDataFile, &currentMissionIndex, sizeof(int), 1);
        vector<string> inventoryItemsNames = getInventory()->getItemNames();
        androidText::saveStringsTofile(binaryDataFile, inventoryItemsNames);
        vector<string> heroItemsNames = getHeroInventory()->getItemNames();
        androidText::saveStringsTofile(binaryDataFile, heroItemsNames);
        SDL_RWclose(binaryDataFile);
    }
}

void GameModel::loadGameData(const std::string& aFileName)
{
    if (!gameDataLoaded)
    {
#ifdef __ANDROID__
        string filename1(SDL_GetPrefPath("darkdefence", "game"));
        filename1.append("save.bin");
#else
        string filename1(aFileName);
#endif

        SDL_RWops* binaryDataFile = SDL_RWFromFile(filename1.c_str(),"r+b");
        if (binaryDataFile != nullptr)
        {
            int goldAmount{};
            SDL_RWread(binaryDataFile, &goldAmount, sizeof(int), 1);
            AccountModel::getInstance()->setGoldAmount(goldAmount);
            SDL_RWread(binaryDataFile, &currentMissionIndex, sizeof(int), 1);

            vector<string> inventoryItemsNames;
            androidText::loadStringsFromfile(binaryDataFile, inventoryItemsNames);

            for(auto itemName : inventoryItemsNames)
                shop->sendItemWithoutPriceCheck(itemName);

            vector<string> heroItemsNames;
            androidText::loadStringsFromfile(binaryDataFile, heroItemsNames);

            for(auto itemName : heroItemsNames)
            {
                shop->sendItemWithoutPriceCheck(itemName);
                inventory->sendItemWithoutPriceCheck(itemName);
            }

            SDL_RWclose(binaryDataFile);
        }

        gameDataLoaded = true;
    }
}

const Reward& GameModel::getMissionReward() const
{
    return missionReward;
}

void GameModel::setMissionReward(const Reward& value)
{
    missionReward = value;
}

void GameModel::loadAbilitiesNames(const std::string& aFileName)
{
    string textString;
    androidText::loadTextFileToString(aFileName, textString);

    if (!textString.empty())
    {
        stringstream abilityStream(textString);

        LOG_INFO("Loading Abilities Names.");

        int n;
        abilityStream >> n;
        if (n > 0)
        {
            abilitiesNames.resize(n);
            for(int i = 0; i < n; ++i)
            {
                abilityStream >> abilitiesNames[i];
            }
        }
    }
}

string GameModel::getAbilityNameFromIndex(size_t index)
{
    return abilitiesNames.at(index);
}

size_t GameModel::getAbilityCount() const
{
    return abilitiesNames.size();
}

void GameModel::calculatePointsPerWave()
{
    pointsPerMap += static_cast<int> (pointsPerWave * pointsRefundModifier);
    pointsPerWave = 0;
}

int GameModel::getPointsPerWave() const
{
    return pointsPerMap;
}

void GameModel::resetGameValues()
{
    pointsRefundModifier = pointsPerMap = pointsPerWave = 0;
    gameStatus = Enums::GameStatuses::gsINPROGRESS;
    MonsterCountOnMap = 0;
    waveNumber = waveCount = 0;
}

void GameModel::setGameStatus(const Enums::GameStatuses& value)
{
    gameStatus = value;

    if (gameStatus == Enums::GameStatuses::gsLOST)
        pointsPerMap = 0;
}

int GameModel::getMonsterCount() const
{
    return MonsterCountOnMap;
}

std::unique_ptr<MineModel> GameModel::getMineModel(const std::string& aName)
{
    return std::make_unique<MineModel>(minesModelsMap.at(aName));
}

std::unique_ptr<MineModel> GameModel::getMineModelByRes(Enums::ResourceTypes resType)
{
    return getMineModel(mineResMapping[static_cast<int>(resType)]);
}

MineModel* GameModel::getMineModelFromList(const string& aName)
{
    return &minesModelsMap.at(aName);
}

MineModel* GameModel::getMineModelFromListByRes(Enums::ResourceTypes resType)
{
    return getMineModelFromList(mineResMapping[static_cast<int>(resType)]);
}

MobModel* GameModel::getMonsterFromListWithName(const std::string& aName)
{
    return &monstersModelsMap[aName];
}

map<string, MobModel>& GameModel::getMonsterList()
{
    return monstersModelsMap;
}

GameModel* GameModel::getInstance()
{
    if (!instance_)
    {
        instance_ = new GameModel();
    }

    return instance_;
}

std::shared_ptr<ResourcesModel> GameModel::getResourcesModel()
{
    return resourcesModelPtr;
}

bool GameModel::loadShopItems(const std::string& aFileName)
{
    if (!shopItemsLoaded)
    {
        string textString;
        androidText::loadTextFileToString(aFileName, textString);

        if (!textString.empty())
        {
            stringstream str(textString);

            LOG_INFO("Loading Shop Items.");

            cereal::XMLInputArchive xmlinp(str);

            xmlinp(shop);
        }

        shop->ConnectModelReceiver(std::bind(&Inventory::receiveItem, inventory, std::placeholders::_1));
        inventory->ConnectModelReceiver(std::bind(&HeroInventory::receiveItem, heroFigure, std::placeholders::_1));
        heroFigure->ConnectModelReceiver(std::bind(&Inventory::receiveItem, inventory, std::placeholders::_1));

        shopItemsLoaded = true;
    }

    return (!shopItemsLoaded);
}

std::shared_ptr<ShopInventory> GameModel::getShopInventory()
{
    return shop;
}

std::shared_ptr<Inventory> GameModel::getInventory()
{
    return inventory;
}

std::shared_ptr<HeroInventory> GameModel::getHeroInventory()
{
    return heroFigure;
}

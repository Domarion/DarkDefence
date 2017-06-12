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

std::unique_ptr<MobModel> GameModel::getMonsterByName(string name)
{
    return std::make_unique<MobModel>(monstersModelsMap[name]);
}

std::unique_ptr<MobModel> GameModel::getTowerByName(string name)
{
    auto temp = towerUpgradesRootNode->recursiveSearch(name);

    if (temp == nullptr)
        return nullptr;

    return std::make_unique<MobModel>(*temp->getData());
}

void GameModel::loadMonsterList(string filename)
{
    list<MobModel> monsterCollection;

    string textString;
    androidText::loadTextFileToString(filename, textString);

    if (!textString.empty())
    {
        stringstream str(textString);

        cereal::XMLInputArchive xmlinp(str);
        xmlinp(cereal::make_nvp("Monsters", monsterCollection));
    }

	for(auto i = monsterCollection.begin(); i != monsterCollection.end(); ++i)
	{
        monstersModelsMap.insert(std::make_pair(i->getName(), *i));
	}
}

void GameModel::loadMonsterPointsList(string filename)
{
    string textString;
    androidText::loadTextFileToString(filename, textString);

    if (!textString.empty())
    {
        stringstream pointStream(textString);

        int n;
        pointStream >> n;
        for(int i = 0; i < n; ++i)
        {
            string str;
            int val;
            pointStream >> str >> val;
            monsterPointsMap[str] =  val;
        }
    }
}

void GameModel::loadTowerUpgrades(string filename)
{
    string textString;
    androidText::loadTextFileToString(filename, textString);

    if (!textString.empty())
    {
        try
        {
            stringstream str(textString);

            cereal::XMLInputArchive xmlinp(str);
            xmlinp(cereal::make_nvp("TowerTree", towerUpgradesRootNode));
        }
        catch(std::exception& ex)
        {
            std::cerr << "Error in loadTowerUpgrades from file: " << ex.what() << std::endl;
        }
    }
}

void GameModel::loadMinesList(string filename)
{
    list<MineModel> mineCollection;

    string textString;
    androidText::loadTextFileToString(filename, textString);

    if (!textString.empty())
    {
        stringstream str(textString);

        cereal::XMLInputArchive xmlinp(str);
        xmlinp(cereal::make_nvp("Mines", mineCollection));

        mineResMapping.resize(mineCollection.size());
    }

    for(auto i = mineCollection.begin(); i != mineCollection.end(); ++i)
    {
        minesModelsMap.insert(std::make_pair(i->getName(), *i));
        mineResMapping[static_cast<int>(i->getProductionType())] = i->getName();
    }
}

void GameModel::deserialize(Mission &obj, string filename)
{
    string textString;
    androidText::loadTextFileToString(filename, textString);

    if (!textString.empty())
    {
        stringstream missionStream(textString);

        cereal::XMLInputArchive xmlinp(missionStream);
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

bool GameModel::canSpawn() const
{
	return (MonsterCountOnMap == 0);
}

void GameModel::incMonsterCount()
{
    ++MonsterCountOnMap;
    std::cout << "MonsterCountOnMap = " << MonsterCountOnMap << std::endl;
}

void GameModel::decMonsterCount(string monsterName)
{
    pointsPerWave += monsterPointsMap[monsterName];
    std::cout << "pointsPerWave = " << pointsPerWave << std::endl;
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

void GameModel::saveGameData(string filename)
{
    string filename1(filename);
    androidText::setRelativePath(filename1);

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

void GameModel::loadGameData(string filename)
{
    if (gameDataLoaded == false)
    {
        string filename1(filename);
        androidText::setRelativePath(filename1);

        SDL_RWops* binaryDataFile = SDL_RWFromFile(filename1.c_str(),"r+b");
        if (binaryDataFile != nullptr)
        {
            int goldAmount{};
            SDL_RWread(binaryDataFile, &goldAmount, sizeof(int), 1);
            AccountModel::getInstance()->setGoldAmount(goldAmount);
            SDL_RWread(binaryDataFile, &currentMissionIndex, sizeof(int), 1);

            std::cout << "HASGOLD=" << AccountModel::getInstance()->getGoldAmount() << std::endl;
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

void GameModel::setMissionReward(const Reward &value)
{
    missionReward = value;
}

void GameModel::loadAbilitiesNames(string filename)
{
    string textString;
    androidText::loadTextFileToString(filename, textString);


    if (!textString.empty())
    {
        stringstream abilityStream(textString);

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

string GameModel::getAbilityNameFromIndex(int index)
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

void GameModel::setGameStatus(const Enums::GameStatuses &value)
{
    gameStatus = value;

    if (gameStatus == Enums::GameStatuses::gsLOST)
        pointsPerMap = 0;
}

int GameModel::getMonsterCount() const
{
    return MonsterCountOnMap;
}

std::unique_ptr<MineModel> GameModel::getMineModel(string name)
{
    return std::make_unique<MineModel>(minesModelsMap.at(name));
}

std::unique_ptr<MineModel> GameModel::getMineModelByRes(Enums::ResourceTypes resType)
{
    return getMineModel(mineResMapping[static_cast<int>(resType)]);
}

MineModel *GameModel::getMineModelFromList(const string& aName)
{
    return &minesModelsMap.at(aName);
}

MineModel *GameModel::getMineModelFromListByRes(Enums::ResourceTypes resType)
{
    return getMineModelFromList(mineResMapping[static_cast<int>(resType)]);
}

MobModel *  GameModel::getMonsterFromListWithName(string name)
{
    return &monstersModelsMap[name];
}

map<string, MobModel> &GameModel::getMonsterList()
{
    return monstersModelsMap;
}

GameModel*  GameModel::getInstance()
{
    if (instance_ == nullptr)
        instance_ = new GameModel();

	return instance_;
}

std::shared_ptr<ResourcesModel> GameModel::getResourcesModel()
{
	return resourcesModelPtr;
}

bool GameModel::loadShopItems(string filename)
{
    if (shopItemsLoaded == false)
    {
        string textString;
        androidText::loadTextFileToString(filename, textString);

        if (!textString.empty())
        {
            stringstream str(textString);


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

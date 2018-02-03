#include "GameModel.h"

#include <functional>
#include <list>
#include <sstream>

#include <boost/filesystem.hpp>
#include <cereal/archives/xml.hpp>
#include <cereal/types/memory.hpp>

#include "../MissionSystem/ResourceGoal.h"
#include "../Utility/textfilefunctions.h"
#include "AccountModel.h"
#include "../Logging/Logger.h"

GameModel* GameModel::instance_ = nullptr;

GameModel::GameModel()
    : shop(std::make_shared<ShopInventory>())
    , heroFigure(std::make_shared<HeroInventory>(9))
    , inventory(std::make_shared<Inventory>())
    , resourcesModelPtr(std::make_shared<ResourcesModel>())
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
    std::list<MobModel> monsterCollection;

    string textString;
    androidText::loadTextFileToString(aFileName, textString);

    if (!textString.empty())
    {
        std::stringstream str(textString);

        cereal::XMLInputArchive xmlinp(str);

        LOG_INFO("Loading Monster std::list.");
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
        std::stringstream pointStream(textString);

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
            std::stringstream str(textString);

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
    std::list<MineModel> mineCollection;

    string textString;
    androidText::loadTextFileToString(aFileName, textString);

    if (!textString.empty())
    {
        std::stringstream str(textString);

        cereal::XMLInputArchive xmlinp(str);

        LOG_INFO("Loading Mines std::list.");

        xmlinp(cereal::make_nvp("Mines", mineCollection));

        mineResMapping.resize(mineCollection.size());
    }

    for(auto i = mineCollection.begin(); i != mineCollection.end(); ++i)
    {
        mineResMapping[i->getProductionTypeIndex()] = i->getName();
        minesModelsMap.emplace(i->getName(), std::move(*i));
    }
}

// deprecated
void GameModel::deserialize(Mission& obj, const std::string& aFileName)
{
    obj.reset();
    string textString;
    androidText::loadTextFileToString(aFileName, textString);

    if (!textString.empty())
    {
        std::stringstream missionStream(textString);

        cereal::XMLInputArchive xmlinp(missionStream);
        LOG_INFO("Loading Mission Info.");

        xmlinp >> cereal::make_nvp("Mission", obj);
    }
}

const std::shared_ptr<TreeNode<MobModel>>& GameModel::getRootTower() const
{
    return towerUpgradesRootNode;
}

void GameModel::addItemToInventoryByName(const std::string& aItemName)
{
    shop->sendItemWithoutPriceCheck(aItemName);
}

bool GameModel::NoMonstersOnMap() const
{
    return (MonsterCountOnMap == 0);
}

void GameModel::incMonsterCount()
{
    ++MonsterCountOnMap;
}

void GameModel::decMonsterCount(const std::string& aMonsterName)
{
    pointsPerWave += monsterPointsMap[aMonsterName];
    --MonsterCountOnMap;
}

void GameModel::setCurrentMissionIndex(int aMissionIndex)
{
    currentMissionIndex = aMissionIndex;
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

void GameModel::setPointsRefundModifier(double aPointsModifier)
{
    pointsRefundModifier = aPointsModifier;
}

void GameModel::addPoints(int aAmount)
{
    pointsPerMap += aAmount;
}


void GameModel::saveGameData(const std::string& aFileName) // TODO : use textFileFunctions
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

void GameModel::loadGameData(const std::string& aFileName) // TODO : use textFileFunctions
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
        std::stringstream abilityStream(textString);

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

const string& GameModel::getAbilityNameFromIndex(size_t aIndex) const
{
    return abilitiesNames.at(aIndex);
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

void GameModel::loadMissions(const std::string& aPath)
{
    using namespace boost::filesystem;
    path missionsRootPath(aPath);

    const directory_iterator end;
    assert(is_directory(missionsRootPath));

    std::vector<Mission> missions;

    for (directory_iterator iter(missionsRootPath); iter != end; ++iter)
    {
        if (is_directory(*iter))
        {
            path missionFilePath = missionsRootPath / iter->path() / "Mission.xml";

            Mission mission;
            string textString;
            androidText::loadTextFileToString(missionFilePath.string(), textString);

            if (!textString.empty())
            {
                std::stringstream missionStream(textString);

                cereal::XMLInputArchive xmlinp(missionStream);
                LOG_INFO("Loading Mission Info.");

                xmlinp >> cereal::make_nvp("Mission", mission);

                missions.emplace_back(mission);
            }
        }
    }

    mMissionsSwitcher.SetMissions(std::move(missions));
}

void GameModel::resetGameValues()
{
    pointsRefundModifier = pointsPerMap = pointsPerWave = 0;
    gameStatus = Enums::GameStatuses::gsINPROGRESS;
    MonsterCountOnMap = 0;
    waveNumber = waveCount = 0;
}

void GameModel::setGameStatus(Enums::GameStatuses aGameStatus)
{
    gameStatus = aGameStatus;

    if (gameStatus == Enums::GameStatuses::gsLOST)
    {
        pointsPerMap = 0;
    }
}

int GameModel::getMonsterCount() const
{
    return MonsterCountOnMap;
}

std::unique_ptr<MineModel> GameModel::getMineModel(const std::string& aName)
{
    return std::make_unique<MineModel>(minesModelsMap.at(aName));
}

std::unique_ptr<MineModel> GameModel::getMineModelByRes(Enums::ResourceTypes aResType)
{
    return getMineModel(mineResMapping[static_cast<int>(aResType)]);
}

MineModel* GameModel::getMineModelFromList(const string& aName)
{
    return &minesModelsMap.at(aName);
}

MineModel* GameModel::getMineModelFromListByRes(Enums::ResourceTypes aResType)
{
    return getMineModelFromList(mineResMapping[Enums::toIntegralType(aResType)]);
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

const std::shared_ptr<ResourcesModel>& GameModel::getResourcesModel() const
{
    return resourcesModelPtr;
}

std::shared_ptr<ResourcesModel> GameModel::getResourcesModelNonConst()
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
            std::stringstream str(textString);

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

const std::shared_ptr<ShopInventory>& GameModel::getShopInventory() const
{
    return shop;
}

const std::shared_ptr<Inventory>& GameModel::getInventory() const
{
    return inventory;
}

const std::shared_ptr<HeroInventory>& GameModel::getHeroInventory() const
{
    return heroFigure;
}

/*
 * GameModel.cpp
 *
 *  Created on: 14 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "GameModel.h"
#include <fstream>
#include <list>
using std::list;
using std::ifstream;
#include <boost/serialization/list.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <iostream>

#include <functional>
#include <boost/mpl/placeholders.hpp>
#include "../MissionSystem/ResourceGoal.h"
#include <iostream>

#include "../AbilitySystem/ItemAbilities/CaftanOfGold.h"
#include "../AbilitySystem/ItemAbilities/ChoppersHat.h"
#include "../AbilitySystem/ItemAbilities/HelmOfLigofglass.h"
#include "../AbilitySystem/ItemAbilities/TitanChock.h"
#include "../AbilitySystem/ItemAbilities/FeatherOfChap.h"

#include "../AbilitySystem/MobAbilities/MobAbilityArson.h"
#include "../AbilitySystem/MobAbilities/MobAbilityRegeneration.h"
#include "../AbilitySystem/MobAbilities/MobAbilitySprint.h"
#include "../Utility/textfilefunctions.h"
#include <sstream>
using std::stringstream;

GameModel* GameModel::instance_ = nullptr;

MobModel* GameModel::getMonsterByName(string name)
{
    return new MobModel(monstersModelsMap[name]);
}

MobModel* GameModel::getTowerByName(string name)
{

    TreeNode<MobModel>* temp = towerUpgradesRootNode.recursiveSearch(name);
    if (temp == nullptr)
        return nullptr;
    return new MobModel(temp->getData());
}

void GameModel::loadMonsterList(string filename)
{


    list<MobModel> monsterCollection;



    string textString;
    androidText::loadTextFileToString(filename, textString);


    if (!textString.empty())
    {
        stringstream str(textString);


        boost::archive::xml_iarchive xmlinp(str);
        xmlinp >> boost::serialization::make_nvp("Monsters",monsterCollection);
    }
/*
    ifstream somestream(filename);
    if (somestream.good())
    {
        boost::archive::xml_iarchive xmlinp(somestream);
        xmlinp >> boost::serialization::make_nvp("Monsters",monsterCollection);
    }


    somestream.close();*/


	for(auto i = monsterCollection.begin(); i != monsterCollection.end(); ++i)
	{
        monstersModelsMap.insert(std::make_pair(i->getName(), *i));
	}

	for(auto i = monstersModelsMap.begin(); i != monstersModelsMap.end(); ++i)
	{

		std::cout << monstersModelsMap[i->first].getName() << std::endl;
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


   /* ifstream pointStream( filename);

    if (pointStream.good())
    {
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
    pointStream.close();*/
}



/*void GameModel::deserialize(MobModel& obj, string filename)
{

    //


}*/

void GameModel::loadTowerUpgrades(string filename)
{

    string textString;
    androidText::loadTextFileToString(filename, textString);


    if (!textString.empty())
    {
        stringstream str(textString);


        boost::archive::xml_iarchive xmlinp(str);
        xmlinp >> boost::serialization::make_nvp("TowerTree", towerUpgradesRootNode);
    }



    /*
	ifstream towerStream(filename);

	std::cout << "ALL GOOD" << std::endl;
	if (towerStream.good())
	{

		boost::archive::xml_iarchive xmlinp(towerStream);
        xmlinp >> boost::serialization::make_nvp("TowerTree", towerUpgradesRootNode);

	}
	std::cout << "ALL GOOD2" << std::endl;
	towerStream.close();
*/

}

void GameModel::loadMinesList(string filename)
{
    list<MineModel> mineCollection;

    string textString;
    androidText::loadTextFileToString(filename, textString);


    if (!textString.empty())
    {
        stringstream str(textString);


        boost::archive::xml_iarchive xmlinp(str);
        // xmlinp.register_type<MineModel>();
        xmlinp >> boost::serialization::make_nvp("Mines", mineCollection);

        mineResMapping.resize(mineCollection.size());
    }


  /*  ifstream somestream(filename);
    std::cout << "fuck0" << std::endl;
    if (somestream.good())
    {
        boost::archive::xml_iarchive xmlinp(somestream);
        // xmlinp.register_type<MineModel>();
        xmlinp >> boost::serialization::make_nvp("Mines", mineCollection);

        mineResMapping.resize(mineCollection.size());
    std::cout << "fuck01" << std::endl;
    }

std::cout << "fuck1" << std::endl;
    somestream.close();

*/
    for(auto i = mineCollection.begin(); i != mineCollection.end(); ++i)
    {
        minesModelsMap.insert(std::make_pair(i->getName(), *i));
    std::cout << "fuck" << std::endl;
        std:: cout << "prodType = " << (i->getProductionType()) << " mineName = " << (i->getName()) << std::endl;
        mineResMapping[i->getProductionType()] = i->getName();
    }

    for(auto i = minesModelsMap.begin(); i != minesModelsMap.end(); ++i)
    {

        std::cout << minesModelsMap[i->first].getName() << std::endl;
    }
}

void GameModel::deserialize(Mission &obj, string filename)
{
    string textString;
    androidText::loadTextFileToString(filename, textString);


    if (!textString.empty())
    {
        stringstream missionStream(textString);


        boost::archive::xml_iarchive xmlinp(missionStream);
        xmlinp.register_type<ResourceGoal>();
        xmlinp >> boost::serialization::make_nvp("Mission", obj);
    }


  /*  ifstream missionStream(filename);

    if (missionStream.good())
    {

        boost::archive::xml_iarchive xmlinp(missionStream);
        xmlinp.register_type<ResourceGoal>();
        xmlinp >> boost::serialization::make_nvp("Mission", obj);

    }

    missionStream.close();*/
}

TreeNode<MobModel>* GameModel::getRootTower()
{
    return &towerUpgradesRootNode;
}

void GameModel::addItemToInventoryByName(string name)
{

    std::cout << "rewItemName = " << name << std::endl;
    ItemModel* item =shop.getItemByName(name);
    if (item != nullptr)
    inventory.addItem(*item);
}

bool GameModel::canSpawn() const
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

GameModel::~GameModel()
{
    delete resourcesModelPtr;
	// TODO Auto-generated destructor stub
}

double GameModel::getPointsRefundModifier() const
{
    return pointsRefundModifier;
}

void GameModel::setPointsRefundModifier(double value)
{
    pointsRefundModifier = value;
}

void GameModel::loadItemAbilities()
{
    itemAbilitiesMap["CaftanOfGold"] = new CaftanOfGold();
    itemAbilitiesMap["ChoppersHat"] = new ChoppersHat(Enums::ResourceTypes::WOOD);
    itemAbilitiesMap["ScabblerHat"] = new ChoppersHat(Enums::ResourceTypes::STONE);
    itemAbilitiesMap["HelmOfLigofglass"] = new HelmOfLigofglass();
    itemAbilitiesMap["TitanChock"] = new TitanChock();
    itemAbilitiesMap["FeatherOfChap"] = new FeatherOfChap();
}

/*void GameModel::loadMobAbilities()
{
    mobAbilitiesMap["MobAbilityArson"]= new MobAbilityArson();
    mobAbilitiesMap["MobAbilityRegeneration"]= new MobAbilityRegeneration();
    mobAbilitiesMap["MobAbilitySprint"] = new MobAbilitySprint();
}*/

ItemAbility *GameModel::getItemAbilityByName(string name)
{
    return itemAbilitiesMap[name];
}

MobAbility *GameModel::getMobAbilityByName(string name)
{
    if (name == "MobAbilityArson")
        return new MobAbilityArson();
    if (name == "MobAbilityRegeneration")
        return new MobAbilityRegeneration();
    if (name == "MobAbilitySprint")
        return new MobAbilitySprint();

    return nullptr;
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
                abilityStream >> abilitiesNames[ i ];
                std::cout << abilitiesNames[i] << std::endl;
            }
        }
    }

    /*
    ifstream abilityStream(filename);
    if (abilityStream.good())
    {
        int n;
        abilityStream >> n;
        if (n > 0)
        {
            abilitiesNames.resize(n);
            for(int i = 0; i < n; ++i)
            {
                abilityStream >> abilitiesNames[ i ];
             //   std::cout << abilitiesNames[i] << std::endl;
            }
        }
    }

    abilityStream.close();*/
}

string GameModel::getAbilityNameFromIndex(int index)
{
    return abilitiesNames[ index ];
}

int GameModel::getAbilityCount() const
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

ManaGlobal *GameModel::getManaModel()
{
    return &manaModel;

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

MineModel *GameModel::getMineModel(string name)
{
    return new MineModel(minesModelsMap[name]);
}

MineModel *GameModel::getMineModelByRes(Enums::ResourceTypes resType)
{

    //std::cout << "Minename=" << mineResMapping[resType] << std::endl;
    return getMineModel(mineResMapping[resType]);
    // return nullptr;
}

MineModel *GameModel::getMineModelFromList(string name)
{
    return &minesModelsMap[name];
}

MineModel *GameModel::getMineModelFromListByRes(Enums::ResourceTypes resType)
{
    return getMineModelFromList(mineResMapping[resType]);
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

ResourcesModel* GameModel::getResourcesModel()
{
	return resourcesModelPtr;
}


GameModel::GameModel()
:waveNumber(0), waveCount(0), pointsPerWave(0), pointsPerMap(0),
 pointsRefundModifier(1), MonsterCountOnMap( 0 ), gameStatus(Enums::GameStatuses::gsINPROGRESS), currentMissionIndex(0), heroFigure(9),
 resourcesModelPtr(new ResourcesModel()), towerUpgradesRootNode(), missionReward()
{

}

void GameModel::loadShopItems(string filename)
{

    string textString;
    androidText::loadTextFileToString(filename, textString);


    if (!textString.empty())
    {
        stringstream str(textString);


        boost::archive::xml_iarchive xmlinp(str);
        xmlinp >> BOOST_SERIALIZATION_NVP(shop);
    }
    /*ifstream somestream(filename);
	if (somestream.good())
	{
        boost::archive::xml_iarchive xmlinp(somestream);
        xmlinp >> BOOST_SERIALIZATION_NVP(shop);
	}

    somestream.close();*/
	//ItemModel empty;
	shop.ConnectMethod(std::bind(&Inventory::receiveItem, &inventory, std::placeholders::_1));
    inventory.ConnectMethod(std::bind(&HeroInventory::receiveItem, &heroFigure, std::placeholders::_1));
    heroFigure.ConnectMethod(std::bind(&Inventory::receiveItem, &inventory, std::placeholders::_1));
}

ShopInventory* GameModel::getShopInventory()
{
	return &shop;
}

Inventory* GameModel::getInventory()
{
    return &inventory;
}

HeroInventory *GameModel::getHeroInventory()
{
    return &heroFigure;

}

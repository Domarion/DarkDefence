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
GameModel* GameModel::instance_ = nullptr;
#include <functional>
#include <boost/mpl/placeholders.hpp>
#include "../MissionSystem/ResourceGoal.h"
#include <iostream>
MobModel* const GameModel::getMonsterByName(string name)
{
    return new MobModel(monstersModelsMap[name]);
}

MobModel* const GameModel::getTowerByName(string name)
{
     return new MobModel(towerUpgradesRootNode.recursiveSearch(name)->getData());
}

void GameModel::loadMonsterList(string filename)
{


    list<MobModel> monsterCollection;

    ifstream somestream(filename);
    if (somestream.good())
    {
        boost::archive::xml_iarchive xmlinp(somestream);
        xmlinp >> boost::serialization::make_nvp("Monsters",monsterCollection);
    }


    somestream.close();


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
    ifstream pointStream( filename);

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
    pointStream.close();
}



/*void GameModel::deserialize(MobModel& obj, string filename)
{

    //


}*/

void GameModel::loadTowerUpgrades(string filename)
{

	ifstream towerStream(filename);

	std::cout << "ALL GOOD" << std::endl;
	if (towerStream.good())
	{

		boost::archive::xml_iarchive xmlinp(towerStream);
        xmlinp >> boost::serialization::make_nvp("TowerTree", towerUpgradesRootNode);

	}
	std::cout << "ALL GOOD2" << std::endl;
	towerStream.close();


}

void GameModel::loadMinesList(string filename)
{
    list<MineModel> mineCollection;

    ifstream somestream(filename);
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

    ifstream missionStream(filename);

    if (missionStream.good())
    {

        boost::archive::xml_iarchive xmlinp(missionStream);
        xmlinp.register_type<ResourceGoal>();
        xmlinp >> boost::serialization::make_nvp("Mission", obj);

    }

    missionStream.close();
}

TreeNode<MobModel>* GameModel::getRootTower()
{
	return &towerUpgradesRootNode;
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
	// TODO Auto-generated destructor stub
}

Reward GameModel::getMissionReward() const
{
    return missionReward;
}

void GameModel::setMissionReward(const Reward &value)
{
    missionReward = value;
}

void GameModel::loadAbilitiesNames(string filename)
{
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

    abilityStream.close();
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
    pointsPerMap += pointsPerWave * pointsRefundModifier;
    pointsPerWave = 0;
}

int GameModel::getPointsPerWave() const
{
    return pointsPerMap;
}

void GameModel::resetGameValues()
{
    pointsPerMap = 0;

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

GameModel* const GameModel::getInstance()
{
    if (instance_ == nullptr)
        instance_ = new GameModel();

	return instance_;
}

ResourcesModel* const GameModel::getResourcesModel()
{
	return resourcesModelPtr;
}


GameModel::GameModel()
:waveNumber(0), waveCount(0), pointsPerWave(0), pointsPerMap(0),
 pointsRefundModifier(1), MonsterCountOnMap( 0 ), gameStatus(Enums::GameStatuses::gsINPROGRESS), currentMissionIndex(0), heroFigure(10),
 resourcesModelPtr(new ResourcesModel()), towerUpgradesRootNode()
{

}

void GameModel::loadShopItems(string filename)
{

	ifstream somestream(filename);
	if (somestream.good())
	{
		boost::archive::xml_iarchive xmlinp(somestream);
		xmlinp >> BOOST_SERIALIZATION_NVP(shop);
	}

	somestream.close();
	//ItemModel empty;
	shop.ConnectMethod(std::bind(&Inventory::receiveItem, &inventory, std::placeholders::_1));
}

ShopInventory* GameModel::getShopInventory()
{
	return &shop;
}

Inventory* GameModel::getInventory()
{
	return &inventory;
}

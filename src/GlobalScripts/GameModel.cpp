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



void GameModel::deserialize(MobModel& obj, string filename)
{

    //


}

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

void GameModel::decMonsterCount()
{
	--MonsterCountOnMap;
}

GameModel::~GameModel()
{
	// TODO Auto-generated destructor stub
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
 pointsRefundModifier(0), MonsterCountOnMap( 0 ), gameStatus(Enums::GameStatuses::gsINPROGRESS), heroFigure(10),
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

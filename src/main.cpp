/*
 * main.cpp
 *
 *  Created on: 8 марта 2016 г.
 *      Author: kostya_hm
 */
#include "GameApp.h"
#include "Grouping/SceneManager.h"
#include "Scenes/MainScene.h"
#include "Scenes/MapMenuScene.h"
#include "Scenes/GameScene.h"
#include "Scenes/InventoryScene.h"
#include "Scenes/ShopScene.h"
#include "Scenes/ScoreScene.h"

#include "GlobalScripts/GameModel.h"


//for test only{
#include <boost/archive/xml_oarchive.hpp>
#include "Mob/MobModel.h"
#include "Mob/MineModel.h"

#include "MissionSystem/ResourceGoal.h"
#include "MissionSystem/Mission.h"
#include <boost/serialization/list.hpp>

#include "Utility/TreeNode.hpp"
#include <fstream>
#include <string>
using std::string;

#include "ItemSystem/ShopInventory.h"

void saveMobModels()
{
    std::string filename = "/home/kostya_hm/MonsterList.xml";


    int prot[]={10,5,0,0};
        int attack[] = {20,0,0,5};
        string name = "Necromant";
        string tag = "Monster";
        list<string> enemyTags;
        enemyTags.push_back("Gates");
        enemyTags.push_back("Mine");
    MobModel monster(name, tag, 100,prot,attack, 100, 0.5,enemyTags);
    monster.setReloadTimeMaximum(3000.0);

    list<string>* abnames = new list<string>();
    abnames->push_back("MobAbilityArson");
    monster.setAbilitiesNames(*abnames);

    list<MobModel> lst;
    lst.push_back(monster);


	std::ofstream ofs(filename);
	if (ofs.good())
	{
		boost::archive::xml_oarchive xmloa (ofs);
		xmloa.register_type<MobModel>();
        xmloa << boost::serialization::make_nvp("Monsters", lst);

	}
	ofs.close();
}


void saveMineModels()
{
    std::string filename = "/home/kostya_hm/MineModels.xml";


    int prot[]={10,5,0,0};
    string name1 = "GoldMine";
    string name2 = "StoneMine";
    string name3 = "SawMill";
    string name4 = "WindMill";
     string tag = "Mine";



    MineModel mine1(name1, tag, 100, prot, Enums::ResourceTypes::GOLD, 20, 5000);
    MineModel mine2(name2, tag, 100, prot, Enums::ResourceTypes::STONE, 20, 5000);
    MineModel mine3(name3, tag, 100, prot, Enums::ResourceTypes::WOOD, 20, 5000);
    MineModel mine4(name4, tag, 100, prot, Enums::ResourceTypes::WHEAT, 20, 5000);


    list<MineModel> lst;
    lst.push_back(mine1);
    lst.push_back(mine2);
    lst.push_back(mine3);
    lst.push_back(mine4);

    std::ofstream ofs(filename);
    if (ofs.good())
    {
        boost::archive::xml_oarchive xmloa (ofs);
        xmloa.register_type<MineModel>();
        xmloa << boost::serialization::make_nvp("Mines", lst);

    }
    ofs.close();
}

void saveTowerTree()
{


    int prot[]={10,5,0,0};
    int attack[] = {20,0,0,5};
    string name = "BasicTower";
    string tag = "Tower";
    list<string> enemyTags;
    enemyTags.push_back("Monster");

    MobModel tower1 (name, tag, 100,prot,attack, 2,0.5,enemyTags);
    MobModel tower2 ("MageTower", tag, 100,prot,attack, 2,0.5,enemyTags);
    //TreeNode(string name, string parent_name, T& newData);
    TreeNode<MobModel> rootNode("BasicTower", "none", tower1);
    rootNode.addChildData("MageTower", tower2);

    std::string filename = "/home/kostya_hm/TowerTree.xml";
	std::ofstream ofs(filename);
	if (ofs.good())
	{
		boost::archive::xml_oarchive xmloa (ofs);
		xmloa.register_type<MobModel>();
        xmloa.register_type<TreeNode<MobModel> >();
        xmloa << boost::serialization::make_nvp("TowerTree",rootNode);


	}
	ofs.close();
}



void saveMission()
{

    Mission some;
    some.setCaption("First Mission");
    some.setDescription("Very simple mission");


    ResourceGoal someGoal;
    someGoal.setNeeded(100);
    someGoal.setDescription("yet another resource mission");

    some.addGoal(&someGoal);

    Reward someReward;
    someReward.addItemName("VampsRod");
    someReward.setGoldCoins(15);
    some.setReward(someReward);

    std::string filename = "/home/kostya_hm/Mission.xml";
    std::ofstream ofs(filename);
    if (ofs.good())
    {
        boost::archive::xml_oarchive xmloa (ofs);
        xmloa.register_type<ResourceGoal>();

        xmloa << boost::serialization::make_nvp("Mission",some);


    }
    ofs.close();
}

void saveItems(const ShopInventory& mob)
{
	std::string filename = "/home/kostya_hm/Items.xml";
	std::ofstream ofs(filename);
	if (ofs.good())
	{
		boost::archive::xml_oarchive xmloa (ofs);
		xmloa.register_type<MobModel>();
		xmloa << BOOST_SERIALIZATION_NVP(mob);

	}
	ofs.close();
}

//for test only}
int main( int argc, char* args[])
{

    //saveMobModels();
//saveMineModels();
  //  saveMission();

    //saveTowerTree();
   // saveMobModels();
	//GameModel::getInstance()->loadMonsterList("/home/kostya_hm/Mob.txt");

	//for test only{
	/*double prot[]={10,5,0,0};
	double attack[] = {20,0,0,5};
	string name = "BasicTower";
	string tag = "BasicTower";
	//MobModel(string aName, string aTag, int aMaxHealth, double aProtection[], double damage[], double distance, double speed);
	MobModel mob(name, tag, 200, prot, attack, 5.0, 0.0);
saveMobModel(mob);*/


/*	TreeNode<MobModel> somenode("integerNode", "none", mob);
	TreeNode<MobModel> some2 ("integerNode2", "integerNode", mob);
	somenode.addChild(some2.getNodeName(), some2);
	save(somenode);

	return 0;
	//for test only}

*/

/*	ShopInventory shopSome;

	ItemModel item1;

	item1.setCaption("GulakiAmulet");
	item1.setDescription("Some");
	item1.setItemType(Enums::ItemTypes::AMULET);
	shopSome.addItemWithPrice(item1, 100);
	ItemModel item2;
	item2.setCaption("ChoppersHat");
	item2.setDescription("Some");
	item2.setItemType(Enums::ItemTypes::HELM);
	shopSome.addItemWithPrice(item2, 50);

	saveItems(shopSome);
	return 0;*/
	MainScene *mainScene = new MainScene();
    MapMenuScene *mapMenuScene = new MapMenuScene();
	GameScene *gameScene = new GameScene();
	InventoryScene *inventoryScene = new InventoryScene();
	ShopScene *shopScene = new ShopScene();
    ScoreScene* scoreScene = new ScoreScene();

	SceneManager *sceneManager = new SceneManager();
	GameApp* app = new GameApp(sceneManager);

	sceneManager->addScene(mainScene, "MainScene");
    sceneManager->addScene(mapMenuScene, "MapMenuScene");
	sceneManager->addScene(gameScene, "GameScene");
	sceneManager->addScene(inventoryScene, "InventoryScene");
	sceneManager->addScene(shopScene, "ShopScene");
    sceneManager->addScene(scoreScene, "ScoreScene");

	bool result = app->GameLoop();

	delete app;

	return result;

}



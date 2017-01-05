#include "DataGenerator.h"
#include <fstream>

#include "ItemSystem/Inventory.h"
#include "MissionSystem/ResourceGoal.h"
#include "MissionSystem/Mission.h"
#include "Mob/MineModel.h"
#include "Mob/MobModel.h"
#include "Utility/TreeNode.hpp"
#include "Mob/EnemyInfo.h"
#include "Utility/textfilefunctions.h"

#include <cereal/archives/xml.hpp>
#include <cereal/types/memory.hpp>
#include <array>
using std::array;
#include "Utility/StructData.hpp"

DataGenerator::DataGenerator()
{

}

void DataGenerator::saveMission()
{
    const string goalDescription = "yet another resource goal";
    const int resourceAmountNeeded = 100;
    auto someGoal = std::make_shared<ResourceGoal>(goalDescription, resourceAmountNeeded, Enums::ResourceTypes::WHEAT);

    const int coinsAmount = 15;
    Reward someReward(coinsAmount);

    const string itemName = "VampsRod";
    someReward.addItemName(itemName);


    const string MissionCaption = "First Mission";
    const string MissionDescription = "Very simple mission";
    Mission someMission(MissionCaption, MissionDescription, someReward);

    someMission.addGoal(someGoal);


    std::string filePath = "/home/kostya_hm/Mission.xml";
    std::ofstream outputXMLFile(filePath);

    if (outputXMLFile.good())
    {
        cereal::XMLOutputArchive xmloa (outputXMLFile);
//        xmloa.registerPolymorphicType("ResourceGoal");
//        xmloa.register_type<ResourceGoal>();

        xmloa << cereal::make_nvp("Mission", someMission);
    }

    outputXMLFile.close();
}

void DataGenerator::saveTowerTree()
{

    string tag = "Tower";
    EnemyInfo enemyInfo("Monster", Enums::EReaction::Attack, 1);
    const int health = 100;
    int protection[] = {10, 5, 0, 0};
    int damage[] = {20, 0, 0, 5};
    int attackDistance = 100;//TODO:единицы измерения?
    int moveSpeed = 0;
    int reloadTime = 1000; //миллисекунд
    int damageArea = 0;
    list<EnemyInfo> enemyTags;
    enemyTags.push_back(enemyInfo);




    string firstTowerName = "WatcherTower";
    auto firstTower = std::make_unique<MobModel>(firstTowerName, tag, health, protection, damage,
                     attackDistance, moveSpeed, reloadTime, damageArea, enemyTags);

    auto rootNode = std::make_shared<TreeNode<MobModel>>(firstTowerName, "none", std::move(firstTower));

    array<string, 4> watcherTowerChildrenNames = {"BallistaTower", "CatapultTower", "MageTower", "ProductivityTower"};

    for(auto& towername : watcherTowerChildrenNames)
    {
        auto watcherTowerChild = std::make_unique<MobModel> (towername, tag, health, protection, damage,
                         attackDistance, moveSpeed, reloadTime, damageArea, enemyTags);
        rootNode->addChildData(towername, std::move(watcherTowerChild));
    }


    array<string, 3> mageTowerChildrenNames = {"WindTower", "EarthTower","CloudTower"};


    auto mageTowerNode = rootNode->recursiveSearch("MageTower");
    if (mageTowerNode != nullptr)
    {
        for(auto& towername : mageTowerChildrenNames)
        {
           auto mageTowerChild = std::make_unique<MobModel> (towername, tag, health, protection, damage,
                             attackDistance, moveSpeed, reloadTime, damageArea, enemyTags);
           mageTowerNode->addChildData(towername, std::move(mageTowerChild));
        }
    }


    std::string filePath = "/home/kostya_hm/TowerTree.xml";
    std::ofstream outputXMLFile(filePath);

    if (outputXMLFile.good())
    {
        try
        {
            cereal::XMLOutputArchive xmloa(outputXMLFile);
            xmloa << cereal::make_nvp("TowerTree", rootNode);
//            boost::archive::xml_oarchive xmloa (outputXMLFile);
//            xmloa.register_type<MobModel>();
//            xmloa.register_type<std::shared_ptr<MobModel>>();
//            xmloa.register_type<std::shared_ptr<TreeNode<MobModel> >>();
        }
        catch(std::exception& ex)
        {
            std::cerr << "Error in saveTowerTree to file: " << ex.what() << std::endl;
        }
    }
    outputXMLFile.close();
}

void DataGenerator::saveMineCollection()
{

    //string goldMineCaption = "GoldMine";
    string stoneMineCaption = "StoneMine";
    string sawMillCaption = "SawMill";
    string windMillCaption = "WindMill";

    string tag = "Mine";

    int protection[]={10, 5, 0, 0};
    const int health = 100;
    const int productionAmount = 20;
    const int productionPeriod = 5000; //миллисекунд

   // MineModel goldMine(goldMineCaption, tag, health,
     //                  protection, Enums::ResourceTypes::GOLD, productionAmount, productionPeriod
       //                );
    MineModel stoneMine(stoneMineCaption, tag, health, protection,
                        Enums::ResourceTypes::STONE, productionAmount, productionPeriod
                        );
    MineModel sawMill(sawMillCaption, tag, health, protection,
                      Enums::ResourceTypes::WOOD, productionAmount, productionPeriod
                      );
    MineModel windMill(windMillCaption, tag, health, protection,
                       Enums::ResourceTypes::WHEAT, productionAmount, productionPeriod
                       );


    list<MineModel> mineList;

    //mineList.push_back(goldMine);
    mineList.push_back(stoneMine);
    mineList.push_back(sawMill);
    mineList.push_back(windMill);


    std::string filePath = "/home/kostya_hm/MineModels.xml";
    std::ofstream outputXMLFile(filePath);

    if (outputXMLFile.good())
    {
        cereal::XMLOutputArchive xmloa (outputXMLFile);
//        xmloa.register_type<MineModel>();
        xmloa(cereal::make_nvp("Mines", mineList));
    }
    outputXMLFile.close();
}

void DataGenerator::saveMonsterCollection()
{
    string tag = "Monster";
    const int health = 100;
    int protection[] = {10, 5, 0, 0};
    int damage[] = {20, 0, 0, 5};

    int attackDistance = 100;//TODO:единицы измерения?
    int moveSpeed = 0.5;//TODO::единицы измерения?
    int reloadTime = 3000; //миллисекунд
    int damageArea = 0;
    EnemyInfo enemyInfoMine("Mine", Enums::EReaction::UseAbilities, 3);
    EnemyInfo enemyInfoGates("Gates", Enums::EReaction::Attack, 1);

    list<EnemyInfo> enemyTags{enemyInfoMine, enemyInfoGates};

    string firstMonsterName = "Necromant";
    MobModel firstMonster (firstMonsterName, tag, health, protection, damage,
                     attackDistance, moveSpeed, reloadTime, damageArea, enemyTags);

    list<string>* abilityNames = new list<string>();
    abilityNames->push_back("MobAbilityArson");
    firstMonster.setAbilitiesNames(*abilityNames);

    list<MobModel> monsterList;
    monsterList.push_back(firstMonster);


    std::string filePath = "/home/kostya_hm/MonsterList.xml";
    std::ofstream outputXMLFile(filePath);

    if (outputXMLFile.good())
    {
        cereal::XMLOutputArchive xmloa(outputXMLFile);
//        xmloa.register_type<MobModel>();
        xmloa(cereal::make_nvp("Monsters", monsterList));

    }
    outputXMLFile.close();
}

void DataGenerator::saveItems()
{
    auto fullInventory = std::make_shared<Inventory>();

    const int firstItemPrice = 100;
    ItemModel firstItem("GulakiAmulet", "Some", Enums::ItemTypes::AMULET, firstItemPrice);

    const int secondItemPrice = 50;
    ItemModel secondItem("ChoppersHat", "Some", Enums::ItemTypes::HELM, secondItemPrice);


    fullInventory->addItem(firstItem);
    fullInventory->addItem(secondItem);

    std::string filePath = "/home/kostya_hm/Items.xml";
    std::ofstream outputXMLFile(filePath);

    if (outputXMLFile.good())
    {
        cereal::XMLOutputArchive xmloa (outputXMLFile);
        xmloa << cereal::make_nvp("Inventory", fullInventory);

    }
    outputXMLFile.close();
}

void DataGenerator::saveAnim()
{
    vector<SDL_Rect> walkRects;
    SDL_Rect rect0 = {13, 7, 42, 73};
    SDL_Rect rect1 = {102, 12, 43, 67};
    SDL_Rect rect2 = {181, 17, 49, 64};
    SDL_Rect rect3 = {267, 13, 47, 67};
    SDL_Rect rect4 = {360, 11, 42, 68};
    SDL_Rect rect5 = {463, 14, 47, 68};
    SDL_Rect rect6 = {568, 18, 49, 65};
    SDL_Rect rect7 = {652, 15, 55, 68};
    walkRects.push_back(rect0);
    walkRects.push_back(rect1);
    walkRects.push_back(rect2);
    walkRects.push_back(rect3);
    walkRects.push_back(rect4);
    walkRects.push_back(rect5);
    walkRects.push_back(rect6);
    walkRects.push_back(rect7);

    map<string, vector<SDL_Rect>> anims;
    anims["Walk"] = walkRects;

    std::string MobAnim = "/home/kostya_hm/Monster.anim";


    SDL_RWops* binaryDataFile = SDL_RWFromFile(MobAnim.c_str(),"w+b");
    if (binaryDataFile != nullptr)
    {
        androidText::saveAnimsToFile(binaryDataFile, anims);
        SDL_RWclose(binaryDataFile);
    }
}

void DataGenerator::savePositions()
{


    vector<StructureData> dataVector{ {"WatcherTower", Size{50, 80}, Position{10, 300}},
                                         {"WatcherTower", Size{50, 80}, Position{60, 300}},
                                         {"WatcherTower", Size{50, 80}, Position{110, 300}},
                                         {"WatcherTower", Size{50, 80}, Position{160, 300}},
                                         {"WatcherTower", Size{50, 80}, Position{210, 300}},
                                         {"Spawner", Size{70, 70}, Position{350, 200}},
                                         {"Gates", Size{80, 80}, Position{20, 150}},
                                         {"ResourceStone", Size{60, 50}, Position{200, 100}}
                                        };

    std::string filePath = "/home/kostya_hm/Positions.xml";
    std::ofstream outputXMLFile(filePath);

    if (outputXMLFile.good())
    {
        cereal::XMLOutputArchive xmloa (outputXMLFile);
        xmloa << cereal::make_nvp("Positions", dataVector);

    }
    outputXMLFile.close();
}

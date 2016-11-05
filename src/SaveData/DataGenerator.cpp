#include "DataGenerator.h"
#include <fstream>
#include <boost/archive/xml_oarchive.hpp>

#include "../MissionSystem/ResourceGoal.h"
#include "../MissionSystem/Mission.h"
#include "../Mob/MineModel.h"
#include "../ItemSystem/ShopInventory.h"
#include "../Mob/MobModel.h"
#include "../Utility/TreeNode.hpp"
#include "../Mob/EnemyInfo.h"
#include "../Utility/textfilefunctions.h"

#include "../SDL_Engine.h"
#include "../GraphicsSystem/newSystem/TileTerrainMaker.h"
#include <array>
using std::array;

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
        boost::archive::xml_oarchive xmloa (outputXMLFile);
        xmloa.register_type<ResourceGoal>();

        xmloa << boost::serialization::make_nvp("Mission", someMission);
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
    MobModel firstTower (firstTowerName, tag, health, protection, damage,
                     attackDistance, moveSpeed, reloadTime, damageArea, enemyTags);

    TreeNode<MobModel> rootNode(firstTower.getName(), "none", firstTower);

    array<string, 4> watcherTowerChildrenNames = {"BallistaTower", "CatapultTower", "MageTower", "ProductivityTower"};

    for(auto& towername : watcherTowerChildrenNames)
    {
        MobModel watcherTowerChild (towername, tag, health, protection, damage,
                         attackDistance, moveSpeed, reloadTime, damageArea, enemyTags);
        rootNode.addChildData(watcherTowerChild.getName(), watcherTowerChild);
    }


    array<string, 3> mageTowerChildrenNames = {"WindTower", "EarthTower","CloudTower"};


    TreeNode<MobModel> *mageTowerNode = rootNode.recursiveSearch("MageTower");
    if (mageTowerNode != nullptr)
    {
        for(auto& towername : mageTowerChildrenNames)
        {
           MobModel mageTowerChild (towername, tag, health, protection, damage,
                             attackDistance, moveSpeed, reloadTime, damageArea, enemyTags);
           mageTowerNode->addChildData(mageTowerChild.getName(), mageTowerChild);
        }
    }


    std::string filePath = "/home/kostya_hm/TowerTree.xml";
    std::ofstream outputXMLFile(filePath);

    if (outputXMLFile.good())
    {
        boost::archive::xml_oarchive xmloa (outputXMLFile);
        xmloa.register_type<MobModel>();
        xmloa.register_type<TreeNode<MobModel> >();
        xmloa << boost::serialization::make_nvp("TowerTree", rootNode);
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
        boost::archive::xml_oarchive xmloa (outputXMLFile);
        xmloa.register_type<MineModel>();
        xmloa << boost::serialization::make_nvp("Mines", mineList);
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
        boost::archive::xml_oarchive xmloa(outputXMLFile);
        xmloa.register_type<MobModel>();
        xmloa << boost::serialization::make_nvp("Monsters", monsterList);

    }
    outputXMLFile.close();
}

void DataGenerator::saveItems()
{
    std::shared_ptr<Inventory> fullInventory = std::make_shared<Inventory>();

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
        boost::archive::xml_oarchive xmloa (outputXMLFile);
        xmloa << boost::serialization::make_nvp("Inventory", fullInventory);

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

void DataGenerator::saveTerrain(std::string filename)
{
    auto SDL2_Library = std::make_unique<SDL2Engine::SDL2>(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    Size scrnSize = Size(800, 480);
    auto renderer = std::make_shared<RenderingSystem>(scrnSize);
    TileLegendCollection tileCollection(renderer);

    std::string str;
    androidText::loadTextFileToString(filename, str);
//    std::string str = "50 50\n2\nt grass\n| rocks\n4 4\n||||\n|tt|\n|tt|\n||||";
    tileCollection.parseString(str);
    using TSurfaceDeleter = void (*)(SDL_Surface *);

    std::unique_ptr<SDL_Surface, TSurfaceDeleter> surface(nullptr, [](SDL_Surface* aSurface){SDL_FreeSurface(aSurface);});
    Texture2D targetTexture = tileCollection.constructTextureByMap(surface);
    std::string destPath = "/home/kostya_hm/terrain.png";

    if (surface == nullptr || surface.get() == nullptr)
        std::cout << "surface is nullptr" << std::endl;
    if (IMG_SavePNG(surface.get(), destPath.c_str())!= 0)
    {
        std::cout << "SDL has error " << IMG_GetError() << std::endl;
    }

    /*int lasttime = SDL_GetTicks();
    const int MS_PER_UPDATE = 16;//1000ms/60FPS
    int lag = 0;

    while(true)
    {

        int currenttime = SDL_GetTicks();

        int elapsed = currenttime - lasttime;
        lasttime = currenttime;
        lag += elapsed;

        while (lag >= MS_PER_UPDATE)
        {
            lag -= MS_PER_UPDATE;
        }

        renderer->renderClear();
        targetTexture.drawAtPosition(Position());
        renderer->renderPresent();
    }*/
}

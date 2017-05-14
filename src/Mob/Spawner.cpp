#include "Spawner.h"
#include "GlobalScripts/GameModel.h"
#include "../Utility/textfilefunctions.h"
#include <cstdlib>
#include <ctime>
#include "GlobalScripts/ResourceManager.h"

Spawner::Spawner()
    : SceneObject()
    , mSpawnerModel()
    , timePeriod(1000)
    , currentTime(timePeriod)
{
    srand (static_cast<unsigned int>(time(NULL)));
}

bool Spawner::update(double timestep)
{
    mSpawnerModel.update(timestep);
    return true; // этот объект не должен быть уничтожен.
}


void Spawner::doSpawn()
{
    if (mSpawnerModel.isSpawned())
    {
        return;
    }

    if (currentTime < timePeriod)
    {
        currentTime += 16; // величина шага времени фиксированная
        return;
    }
//        string monsterName = monsterInfo.first;
//        int monsterCount = monsterInfo.second;

//        for(int index = 0; index < monsterCount; ++index)
//        {
//            auto someMob = std::make_shared<Mob>(GameModel::getInstance()->getMonsterByName(monsterName), aTileMap);


//            if (someMob->getTileMapManager() == nullptr)
//            {
//                std::cout << "someMob->getTileMapManager = nullptr" << std::endl;
//            }
//            auto someSprite = std::make_shared<AnimationSceneSprite>(aRenderingContext);

//            std::string temp = "Spider2";

//            someSprite->setSize(Size(150, 125));
//            someSprite->loadTexture("GameData/textures/Monsters/" + temp + ".png");

//            map<string, vector<SDL_Rect> > anims;

//            std::string filename = "GameData/anims/Monsters/" + temp + ".anim";
//            androidText::setRelativePath(filename);
//            androidText::loadAnimFromFile(filename, anims);

    currentTime = 0;

    auto nextMobName = mSpawnerModel.getNextMobName();

    if (nextMobName == "none")
    {
        currentTime = timePeriod;
//        std::cout << "NO NAME" << std::endl;
        return;
    }

    if (mSpawnCallBack)
    {
        mSpawnCallBack(nextMobName, getRealPosition());
    }
}

void Spawner::connectInfoProcesser(std::function<void (std::string)> aInfoProcesser)
{
    mSpawnerModel.connectInfoProcesser(aInfoProcesser);
}

void Spawner::disconnectInfoProcesser()
{
    mSpawnerModel.disconnectInfoProcesser();
}

void Spawner::disconnectSpawnCallback()
{
    mSpawnCallBack = nullptr;
}

void Spawner::loadWavesInfo()
{
    mSpawnerModel.loadWavesInfo("GameData/wavesInfo.txt");
}

void Spawner::connectSpawnCallBack(std::function<void (std::string, Position)> aCallBack)
{
    mSpawnCallBack = aCallBack;
}

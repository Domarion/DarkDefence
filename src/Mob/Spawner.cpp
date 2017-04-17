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


void Spawner::doSpawn(std::shared_ptr<RenderingSystem>& aRenderingContext, std::shared_ptr<TileMapManager> aTileMap)
{
    if (mSpawnerModel.isSpawned())
    {
        return;
    }

    if (aTileMap == nullptr)
    {
        std::cout << "doSpawn aTileMap nullptr" << std::endl;
    }


    if (currentTime < timePeriod)
    {
        currentTime += 16; // величина шага времени фиксированная
        return;
    }

    currentTime = 0;

    auto nextMobName = mSpawnerModel.getNextMobName();

    if (nextMobName == "none")
    {
        currentTime = timePeriod;
        std::cout << "NO NAME" << std::endl;
        return;
    }

    auto tileMapCopy = std::make_shared<TileMapManager>(*aTileMap);
    auto someMob = std::make_shared<Mob>(GameModel::getInstance()->getMonsterByName(nextMobName), tileMapCopy);


    if (someMob->getTileMapManager() == nullptr)
    {
        std::cout << "someMob->getTileMapManager = nullptr" << std::endl;
    }
    auto someSprite = std::make_shared<AnimationSceneSprite>(aRenderingContext);


    someSprite->setTexture(ResourceManager::getInstance()->getTexture(nextMobName));

    map<string, vector<SDL_Rect> > anims;

    std::string filename = "GameData/anims/Monsters/" + nextMobName + ".anim";
    androidText::setRelativePath(filename);
    androidText::loadAnimFromFile(filename, anims);

    for(auto& anim : anims)
    {
        someSprite->setAnimRects(anim.first, anim.second);
    }

    someMob->setSprite(someSprite);
    getParentScene()->spawnObject(getRealPosition().x, getRealPosition().y, someMob);

//    std::vector<std::pair<std::string, int> > waveInfo = mSpawnerModel.getCurrentWaveInfo();


//    for(const auto& monsterInfo : waveInfo)
//    {
//        string monsterName = monsterInfo.first;
//        int monsterCount = monsterInfo.second;

//        for(int index = 0; index < monsterCount; ++index)
//        {

//            auto tileMapCopy = std::make_shared<TileMapManager>(*aTileMap);
//            auto someMob = std::make_shared<Mob>(GameModel::getInstance()->getMonsterByName(monsterName), tileMapCopy);


//            if (someMob->getTileMapManager() == nullptr)
//            {
//                std::cout << "someMob->getTileMapManager = nullptr" << std::endl;
//            }
//            auto someSprite = std::make_shared<AnimationSceneSprite>(aRenderingContext);


//            someSprite->setTexture(ResourceManager::getInstance()->getTexture(monsterName));
////            std::cout << monsterName << std::endl;
////            someSprite->setSize(Size( 50, 80));
////            someSprite->loadTexture("GameData/textures/Monsters/" + monsterName + "Sheet.png");



//            map<string, vector<SDL_Rect> > anims;

//            std::string filename = "GameData/anims/Monsters/" + monsterName + ".anim";
//            androidText::setRelativePath(filename);
//            androidText::loadAnimFromFile(filename, anims);

//            for(auto& anim : anims)
//            {
//                someSprite->setAnimRects(anim.first, anim.second);
//            }

////            int x = rand() % 10 + 1;
////            int y = rand() % 7 + 1;

//            someMob->setSprite(someSprite);
//            getParentScene()->spawnObject(getPosition().x - /*x **/ 15, getPosition().y /*- y * 10*/, someMob);

//        }
//    }
}

void Spawner::connectInfoProcesser(std::function<void (std::string)> aInfoProcesser)
{
    mSpawnerModel.connectInfoProcesser(aInfoProcesser);
}

void Spawner::disconnectInfoProcesser()
{
    mSpawnerModel.disconnectInfoProcesser();
}

void Spawner::loadWavesInfo()
{
    mSpawnerModel.loadWavesInfo("GameData/wavesInfo.txt");
}

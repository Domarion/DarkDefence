#include "Spawner.h"
#include "GlobalScripts/GameModel.h"
#include "../Utility/textfilefunctions.h"
#include <cstdlib>
#include <ctime>

Spawner::Spawner()
    : SceneObject()
    , mSpawnerModel()
{
    srand (static_cast<unsigned int>(time(NULL)));
}

bool Spawner::update(double timestep)
{
    //mSpawnerModel.canSpawn(timestep);
    //mSpawnerModel.getWaveStringInfo();
    mSpawnerModel.update(timestep);
    return true;
}


void Spawner::doSpawn(std::shared_ptr<RenderingSystem>& aRenderingContext, std::shared_ptr<TileMapManager> aTileMap)
{
    if (mSpawnerModel.isSpawned())
        return;

    std::vector<std::pair<std::string, int> > waveInfo = mSpawnerModel.getCurrentWaveInfo();

    if (aTileMap == nullptr)
    {
        std::cout << "doSpawn aTileMap nullptr" << std::endl;
    }

    for(const auto& monsterInfo : waveInfo)
    {
        string monsterName = monsterInfo.first;
        int monsterCount = monsterInfo.second;

        for(int index = 0; index < monsterCount; ++index)
        {
            auto someMob = std::make_shared<Mob>(GameModel::getInstance()->getMonsterByName(monsterName), aTileMap);


            if (someMob->getTileMapManager() == nullptr)
            {
                std::cout << "someMob->getTileMapManager = nullptr" << std::endl;
            }
            auto someSprite = std::make_shared<AnimationSceneSprite>(aRenderingContext);


            someSprite->setSize(Size( 50, 80));
            someSprite->loadTexture("GameData/textures/Monsters/" + monsterName + "Sheet.png");



            map<string, vector<SDL_Rect> > anims;

            std::string filename = "GameData/anims/Monsters/" + monsterName + ".anim";
            androidText::setRelativePath(filename);
            androidText::loadAnimFromFile(filename, anims);

            for(auto& anim : anims)
            {
                someSprite->setAnimRects(anim.first, anim.second);
            }

//            int x = rand() % 10 + 1;
//            int y = rand() % 7 + 1;

            someMob->setSprite(someSprite);
            getParentScene()->spawnObject(getPosition().x - /*x **/ 15, getPosition().y /*- y * 10*/, someMob);

        }
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

void Spawner::loadWavesInfo()
{
    mSpawnerModel.loadWavesInfo("GameData/wavesInfo.txt");
}

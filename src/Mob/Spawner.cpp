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
    if (!mSpawnerModel.IsReadyForSpawn())
    {
        return;
    }

    if (currentTime < timePeriod)
    {
        currentTime += 16; // величина шага времени фиксированная
        return;
    }

    currentTime = 0;

    auto nextMobName = mSpawnerModel.getMobNameToSpawn();

    if (nextMobName.empty())
    {
        currentTime = timePeriod;
        mDrawPriority = mInitialDrawPriority;
        return;
    }

    ++mDrawPriority;
    if (mSpawnCallBack)
    {
        mSpawnCallBack(nextMobName, getRealPosition(), mDrawPriority);
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

void Spawner::loadWavesInfo(const std::string& aFilePath)
{
    mSpawnerModel.loadWavesInfo(aFilePath);
}

void Spawner::connectSpawnCallBack(std::function<void(std::string, Position, size_t)> aCallBack)
{
    mSpawnCallBack = aCallBack;
}

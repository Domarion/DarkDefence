#include "MobSpawner.h"
#include "GlobalScripts/GameModel.h"
#include "../Utility/textfilefunctions.h"
#include <cassert>
#include <sstream>

void MobSpawner::loadWavesInfo(const std::string& aFilename)
{
    string textString;
    androidText::loadTextFileToString(aFilename, textString);

    if (!textString.empty())
    {
        std::stringstream file0(textString);

        file0 >> waveCount;
        waveMobList.resize(waveCount);
        while(!file0.eof())
        {
            size_t waveNum{};
            string mobName;
            int mobCount{};
            file0 >> waveNum >> mobName >> mobCount;

            if (waveNum > 0)
            {
                waveMobList[waveNum - 1].push_back(std::make_pair(mobCount, mobName));
            }
        }
    }
}

bool MobSpawner::canSpawn(double aTimeStep)
{
    if (GameModel::getInstance()->NoMonstersOnMap())
    {

        if (waveNumber == waveCount)
            return false;

		if (currentTime > 0.0)
            currentTime -= aTimeStep;
		else
		{
            ++waveNumber;

			currentTime = period;
            GameModel::getInstance()->calculatePointsPerWave();
			return true;
		}
    }
    return false;
}

bool MobSpawner::IsReadyForSpawn() const
{
    return !waveMobList.empty()
        && waveNumber >= 1
        && waveNumber <= waveCount
        && (currentSpawnStatus == SpawnStatusT::InProgress);
}


bool MobSpawner::noMoreWaves() const
{
    return (waveNumber == waveCount)
        && GameModel::getInstance()->NoMonstersOnMap()
        && currentSpawnStatus == SpawnStatusT::NoSpawn;
}

double MobSpawner::getCurrentTime() const
{
    return currentTime;
}

bool MobSpawner::isSpawned() const
{
    return currentSpawnStatus != SpawnStatusT::InProgress;
}


size_t MobSpawner::getWaveNumber() const
{
    return waveNumber;
}

size_t MobSpawner::getWaveCount() const
{
    return waveCount;
}

void MobSpawner::reset()
{
    waveNumber = waveCount = 0;
    currentTime = period;
    waveMobList.clear();
    previousValue.clear();
    currentSpawnStatus = SpawnStatusT::NoSpawn;
}

std::string MobSpawner::getMobNameToSpawn()
{
    assert(waveNumber > 0 && waveNumber <= waveCount);
    assert(!waveMobList.empty());

    auto& currentWaveMobList = waveMobList[waveNumber - 1];

    if (currentWaveMobList.empty())
    {
        currentSpawnStatus = SpawnStatusT::Done;
        return "";
    }

    auto& mobInfo = currentWaveMobList.front();
    if (mobInfo.first > 1)
    {
        --mobInfo.first;
        return mobInfo.second;
    }

    std::string mobName = mobInfo.second;
    currentWaveMobList.pop_front();

    return mobName;
}

void MobSpawner::connectInfoProcesser(std::function<void (std::string)> aInfoProcesser)
{
    mInfoProcesser = aInfoProcesser;
}

void MobSpawner::update(double aTimeStep)
{
    const double Eps = 1e-3;
    std::string info;

    switch (currentSpawnStatus)
    {
    case SpawnStatusT::NoSpawn:
        if (GameModel::getInstance()->NoMonstersOnMap())
        {
            if (waveNumber != waveCount)
            {
                if (currentTime > Eps)
                {
                    int i = static_cast<int>(currentTime)/1000;
                    info = "Wave in: " + std::to_string(i);
                    currentTime -= aTimeStep;
                }
                else
                {
                    ++waveNumber;

                    currentTime = period;

                    GameModel::getInstance()->calculatePointsPerWave();


                    info = std::to_string(waveNumber) + " / " + std::to_string(waveCount);

                    currentSpawnStatus = SpawnStatusT::InProgress;
                }
            }
            else
            {
                info = "No more waves";
            }
        }
        break;

    case SpawnStatusT::InProgress:
        info = "InProgress";
        break;

    case SpawnStatusT::Done:
        currentSpawnStatus = SpawnStatusT::NoSpawn;
        break;

    default:
        break;
    }

    if (mInfoProcesser && !info.empty())
    {
        mInfoProcesser(info);
    }
}

void MobSpawner::disconnectInfoProcesser()
{
    mInfoProcesser = nullptr;
}



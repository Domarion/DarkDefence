/*
 * MobSpawner.cpp
 *
 *  Created on: 6 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "MobSpawner.h"
#include "GlobalScripts/GameModel.h"
#include "../Utility/textfilefunctions.h"
#include <fstream>
#include <sstream>
#include <cassert>
using std::stringstream;

MobSpawner::MobSpawner()
    : period(5000)
    , currentTime(period)
    , waveNumber(0)
    , waveCount(0)
    , currentSpawnStatus(SpawnStatusT::NoSpawn)
    , waveMobList()
{
}

void MobSpawner::loadWavesInfo(string filename)
{
    string textString;
    androidText::loadTextFileToString(filename, textString);

    if (!textString.empty())
    {
        stringstream file0(textString);

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

bool MobSpawner::canSpawn(double timestep)
{
    if (GameModel::getInstance()->NoMonstersOnMap())
    {

        if (waveNumber == waveCount)
            return false;

		if (currentTime > 0.0)
			currentTime -= timestep;
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

void MobSpawner::update(double timestep)
{
    const double Eps = 1e-3;
    std::string info {"none"};

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
                    currentTime -= timestep;
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

    if (mInfoProcesser && info != "none")
    {
        mInfoProcesser(info);
    }
}

void MobSpawner::disconnectInfoProcesser()
{
    mInfoProcesser = nullptr;
}



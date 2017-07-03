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
    , wavesInfo()
    , currentSpawnStatus(SpawnStatusT::NoSpawn)
    , nextInfo{-1, "none", 0}
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
        wavesInfo.resize(waveCount);
        while(!file0.eof())
        {
            size_t waveNum{};
            string mobName;
            int mobCount{};
            file0 >> waveNum >> mobName >> mobCount;
            if (waveNum != 0)
            {
                wavesInfo[waveNum - 1].push_back(std::make_pair(mobName, mobCount));
            }
        }
    }
}

bool MobSpawner::canSpawn(double timestep)
{
    if (GameModel::getInstance()->canSpawn())
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



bool MobSpawner::noMoreWaves() const
{
    return (waveNumber == waveCount)
        && GameModel::getInstance()->canSpawn()
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
    wavesInfo.clear();
    previousValue.clear();
    nextInfo = std::make_tuple(-1, "none", 0);
    currentSpawnStatus = SpawnStatusT::NoSpawn;
}


std::vector<std::pair<string, int> > MobSpawner::getCurrentWaveInfo() // deprecated
{
    return wavesInfo[waveNumber - 1];
}

string MobSpawner::getNextMobName()
{
    //TODO Переписать этот запутанный код
    if (waveNumber == 0 || currentSpawnStatus == SpawnStatusT::Done)
    {
        return std::string{"none"};
    }

    const auto& currentWaveInfo = wavesInfo[waveNumber - 1];
    assert(!currentWaveInfo.empty() && "!currentWaveInfo.empty()");

    int index = std::get<0>(nextInfo);
    if (index < 0)
    {
        index = 0;
        auto count = currentWaveInfo[index].second;
        nextInfo = std::make_tuple(index, currentWaveInfo[index].first, count - 1);
        return currentWaveInfo[index].first;
    }

    if (index < currentWaveInfo.size())
    {
        std::string nextMobName = std::get<1>(nextInfo);
        assert(!nextMobName.empty() && nextMobName != "none");
        assert(currentWaveInfo[index].first == nextMobName && "nextMobName is not equal to waveInfo");
        int leavesCount = std::get<2>(nextInfo);
        if (leavesCount == 0 && currentWaveInfo.size() > index + 1)
        {
            ++index;
            auto count = currentWaveInfo[index].second;

            nextInfo = std::make_tuple(index, currentWaveInfo[index].first, count);

            return currentWaveInfo[index].first;
        }

        if (leavesCount <= 0 && currentWaveInfo.size() <= index + 1)
        {

            nextInfo = std::make_tuple(-1, "none", 0);
            currentSpawnStatus = SpawnStatusT::Done;
            return std::string{"none"};
        }

        nextInfo = std::make_tuple(index, nextMobName, --leavesCount);
        return nextMobName;
    }

    if (index >= currentWaveInfo.size())
    {
        nextInfo = std::make_tuple(-1, "none", 0);
    }

    return std::string{"none"};
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
        if (GameModel::getInstance()->canSpawn())
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



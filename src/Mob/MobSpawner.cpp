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
using std::stringstream;

MobSpawner::MobSpawner()
    : period(5000)
    , currentTime(period)
    , waveNumber(0)
    , waveCount(0)
    , wavesInfo()

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
            if (waveNum <= 0)
                throw std::logic_error("WaveNum shold be greater than zero");
            wavesInfo[waveNum - 1].push_back(std::make_pair(mobName, mobCount));
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
    return (waveNumber == waveCount) && GameModel::getInstance()->canSpawn();
}

double MobSpawner::getCurrentTime() const
{
    return currentTime;
}

bool MobSpawner::isSpawned() const
{
    return !GameModel::getInstance()->canSpawn();
}



int MobSpawner::getWaveNumber() const
{
    return waveNumber;
}

int MobSpawner::getWaveCount() const
{
    return waveCount;
}

string MobSpawner::getWaveStringInfo()
{
    string s = "none";

    if (noMoreWaves())
        s = "No More Waves";
    else
    {
        if (!GameModel::getInstance()->canSpawn())
        {
            s = std::to_string(waveNumber) + " / " + std::to_string(waveCount);

        }
        else
        if (currentTime > 0.0)
        {
            int i = static_cast<int>(currentTime)/1000;
            s = "Wave in: " + std::to_string(i);

        }
    }

    if (mInfoProcesser && previousValue != s && s != "none")
    {
        mInfoProcesser(s);
        previousValue = s;
    }
   return s;

}

void MobSpawner::reset()
{
    waveNumber = waveCount = 0;
    currentTime = period;
    wavesInfo.clear();
}


std::vector<std::pair<string, int> > MobSpawner::getCurrentWaveInfo()
{
    return wavesInfo[waveNumber - 1];
}

void MobSpawner::connectInfoProcesser(std::function<void (std::string)> aInfoProcesser)
{
    mInfoProcesser = aInfoProcesser;
}

void MobSpawner::update(double timestep)
{
    if (GameModel::getInstance()->canSpawn())
    {
        std::string info{"none"};

        if (waveNumber != waveCount)
        {
            if (currentTime > 1e-3)
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


            }
        }
        else
            info = "No more waves";

        if (mInfoProcesser)
        {
            mInfoProcesser(info);
        }
    }
}

void MobSpawner::disconnectInfoProcesser()
{
    mInfoProcesser = nullptr;
}



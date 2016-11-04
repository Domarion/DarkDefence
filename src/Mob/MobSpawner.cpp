/*
 * MobSpawner.cpp
 *
 *  Created on: 6 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "MobSpawner.h"
#include "../Utility/textfilefunctions.h"
#include "../GlobalScripts/GameModel.h"
#include <fstream>
#include <sstream>
using std::stringstream;

MobSpawner::MobSpawner(std::shared_ptr<RenderingSystem> &aRenderingContext)
    : renderer(aRenderingContext)
    , period(5000)
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



std::unique_ptr<list<std::shared_ptr<Mob>>> MobSpawner::doSpawn(std::shared_ptr<TileMapManager> aTileMap)
{
    auto some = std::make_unique<std::list<shared_ptr<Mob>>>();
    size_t n = wavesInfo[waveNumber - 1].size();
    std::cout << n << std::endl;
    if (aTileMap == nullptr)
    {
        std::cout << "doSpawn aTileMap nullptr" << std::endl;
    }
    for(size_t i = 0; i < n; ++i)
    {
        string monsterName = (wavesInfo[waveNumber - 1])[i].first;
        int monsterCount = (wavesInfo[waveNumber - 1])[i].second;

        for(int index = 0; index < monsterCount; ++index)
        {
            auto someMob = std::make_shared<Mob>(GameModel::getInstance()->getMonsterByName(monsterName), aTileMap);


            if (someMob->getTileMapManager() == nullptr)
            {
                std::cout << "someMob->getTileMapManager = nullptr" << std::endl;
            }
            auto someSprite = std::make_shared<AnimationSceneSprite>(renderer);


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

            someMob->setSprite(someSprite);
            some->push_back(someMob);

            if (someMob->getTileMapManager() == nullptr)
            {
                std::cout << "someMob->getTileMapManager = nullptr1" << std::endl;
            }
        }
    }

    return some;

}

bool MobSpawner::noMoreWaves() const
{
    return (waveNumber == waveCount) && GameModel::getInstance()->canSpawn();
}

double MobSpawner::getCurrentTime() const
{
    return currentTime;
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

   return s;

}

void MobSpawner::reset()
{
    waveNumber = waveCount = 0;
    currentTime = period;
    wavesInfo.clear();
}



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
#include "../GraphicsSystem/UI/AnimatedSprite.h"

#include <sstream>
using std::stringstream;

MobSpawner::MobSpawner()
    : period(5000), currentTime(period), waveNumber(0), waveCount(0)

{
	// TODO Auto-generated constructor stub

}

MobSpawner::~MobSpawner()
{
    // TODO Auto-generated destructor stub
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
            int waveNum;
            string mobName;
            int mobCount;
            file0 >> waveNum >> mobName >> mobCount;
            wavesInfo[waveNum - 1].push_back(std::make_pair(mobName, mobCount));
        }
    }

}

bool MobSpawner::canSpawn(double timestep)
{
   // std::cout << "Monster Count = " << (GameModel::getInstance()->getMonsterCount()) << std::endl;
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



list<Mob *> *MobSpawner::doSpawn(TileMapManager* aTileMap)
{

    list<Mob*> *some = new list<Mob*>();
    int n = wavesInfo[waveNumber - 1].size();
    std::cout << n << std::endl;
    if (aTileMap == nullptr)
     {
        std::cout << "doSpawn aTileMap nullptr" << std::endl;
    }
    for(int i = 0; i < n; ++i)
    {
        string monsterName = (wavesInfo[waveNumber - 1])[i].first;
        int monsterCount = (wavesInfo[waveNumber - 1])[i].second;

        for(int index = 0; index < monsterCount; ++index)
        {
            Mob* someMob = new Mob(GameModel::getInstance()->getMonsterByName(monsterName), aTileMap);


            if (someMob->getTileMapManager() == nullptr)
            {
                std::cout << "someMob->getTileMapManager = nullptr" << std::endl;
            }
           AnimatedSprite* someSprite = new AnimatedSprite();

            someSprite->setRect(0,0, 50, 80);
            someSprite->loadTexture("GameData/textures/Monsters/" + monsterName + "Sheet.png");

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

            someSprite->setAnimRects("Walk", walkRects);
            someMob->setSprite(someSprite);
            //someMob->init();
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



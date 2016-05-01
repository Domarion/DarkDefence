/*
 * MobSpawner.cpp
 *
 *  Created on: 6 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "MobSpawner.h"
#include "../GlobalScripts/GameModel.h"
#include <fstream>

MobSpawner::MobSpawner()
    : period(200), currentTime(period), waveNumber(0), waveCount(0)

{
	// TODO Auto-generated constructor stub

}

MobSpawner::~MobSpawner()
{
    // TODO Auto-generated destructor stub
}

void MobSpawner::loadWavesInfo(string filename)
{

    std::ifstream file0(filename);
    if (file0.good())
    {
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
    file0.close();
}

bool MobSpawner::canSpawn(double timestep)
{
    //if (GameModel::getInstance()->canSpawn())
    //{

		if (currentTime > 0.0)
			currentTime -= timestep;
		else
		{
            ++waveNumber;
            if (waveNumber > waveCount)
                return false;
			currentTime = period;
			return true;
		}
    //}
	return false;
}

list<SceneObject*>* MobSpawner::doSpawn(SDL_Renderer* renderer)
{

    list<SceneObject*> *some = new list<SceneObject*>();
    int n = wavesInfo[waveNumber - 1].size();
    std::cout << n << std::endl;
    for(int i = 0; i < n; ++i)
    {
        string monsterName = (wavesInfo[waveNumber - 1])[i].first;
        int monsterCount = (wavesInfo[waveNumber - 1])[i].second;

        for(int index = 0; index < monsterCount; ++index)
        {
         Mob* someMob = new Mob(GameModel::getInstance()->getMonsterByName(monsterName));

         Sprite* someSprite = new Sprite();
         someSprite->setRenderer(renderer);
         someSprite->setRect(new SDL_Rect({0,0, 50, 80}));
         someSprite->loadTextureFromFile("/home/kostya_hm/Projects/DarkDefence/GameData/textures/Monsters/" + monsterName + ".png");
         someMob->setSprite(someSprite);
         someMob->init();
         some->push_back(someMob);
        }
    }



	return some;

}
/*
Mob * const TowerFabric::produceTower(std::string towerName, SDL_Renderer* renderer)
{
    MobModel* model = GameModel::getInstance()->getTowerByName(towerName);

    Mob* someMob = new Mob(model);
    Sprite* someSprite = new Sprite();
    someSprite->setRenderer(renderer);
    someSprite->setRect(new SDL_Rect({0,0, 50, 80}));
    someSprite->loadTextureFromFile("/home/kostya_hm/Projects/DarkDefence/GameData/textures/Towers/" + towerName + ".png");
    someMob->setSprite(someSprite);
    someMob->init();
    return someMob;
}*/


/*
 * MobSpawner.h
 *
 *  Created on: 6 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once
//#include "../Grouping/SceneObjectFabric.h"
#include "Mob.h"
#include <utility>
#include <vector>
#include "../GlobalScripts/TileMapManager.h"
class Mob;
class MobSpawner//: SceneObjectFabric
{
public:
	MobSpawner();
	virtual ~MobSpawner();
    void loadWavesInfo(string filename);
	bool canSpawn(double timestep);
    list<Mob*> * doSpawn(TileMapManager* aTileMap = nullptr);
    bool noMoreWaves() const;
    double getCurrentTime() const;

    int getWaveNumber() const;
    int getWaveCount() const;
    string getWaveStringInfo();
    void reset();
private:
    double period;
    double currentTime;
    int waveNumber, waveCount;
    std::vector<std::vector<std::pair<string, int> > > wavesInfo;

};

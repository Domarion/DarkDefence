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

class Mob;
class MobSpawner//: SceneObjectFabric
{
public:
	MobSpawner();
	virtual ~MobSpawner();
    void loadWavesInfo(string filename);
	bool canSpawn(double timestep);
    list<SceneObject*> * doSpawn();
    bool noMoreWaves() const;
private:
	double period;
	double currentTime;
    int waveNumber, waveCount;
    std::vector<std::vector<std::pair<string, int> > >wavesInfo;
    //SceneObjectFabric* fabric;
};

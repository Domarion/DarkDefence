/*
 * MobSpawner.h
 *
 *  Created on: 6 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once

#include "Mob.h"
#include <utility>
#include <vector>
#include "../GlobalScripts/TileMapManager.h"

class MobSpawner
{
public:
    MobSpawner(std::shared_ptr<RenderingSystem>& aRenderingContext);
    virtual ~MobSpawner() = default;
    void loadWavesInfo(string filename);
	bool canSpawn(double timestep);
    std::unique_ptr<list<std::shared_ptr<Mob> > > doSpawn(std::shared_ptr<TileMapManager> aTileMap = nullptr);
    bool noMoreWaves() const;
    double getCurrentTime() const;

    int getWaveNumber() const;
    int getWaveCount() const;
    string getWaveStringInfo();
    void reset();
private:
    std::shared_ptr<RenderingSystem> renderer;
    double period;
    double currentTime;
    size_t waveNumber, waveCount;
    std::vector<std::vector<std::pair<string, int> > > wavesInfo;

};

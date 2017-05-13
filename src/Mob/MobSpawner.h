/*
 * MobSpawner.h
 *
 *  Created on: 6 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include <string>
#include <utility>
#include <vector>
#include <functional>

using std::string;

class MobSpawner
{
public:
    enum class SpawnStatusT
    {
        NoSpawn = 0,
        InProgress,
        Done
    };

public:
    MobSpawner();
    void loadWavesInfo(std::string filename);
	bool canSpawn(double timestep);
    bool noMoreWaves() const;
    double getCurrentTime() const;
    bool isSpawned() const;
    int getWaveNumber() const;
    int getWaveCount() const;
    void reset();
    std::vector<std::pair<string, int> > getCurrentWaveInfo();
    void connectInfoProcesser(std::function<void(string)> aInfoProcesser);
    void update(double timestep);
    void disconnectInfoProcesser();
    string getNextMobName();
private:
    double period;
    double currentTime;
    size_t waveNumber, waveCount;
    std::vector<std::vector<std::pair<string, int> > > wavesInfo;
    std::function<void(string)> mInfoProcesser;
    std::string previousValue{};
    SpawnStatusT currentSpawnStatus;
    std::tuple<int, string, int> nextInfo;
};

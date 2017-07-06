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
#include <deque>

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
    bool IsReadyForSpawn() const;
    bool noMoreWaves() const;
    double getCurrentTime() const;
    bool isSpawned() const;
    size_t getWaveNumber() const;
    size_t getWaveCount() const;
    void reset();
    void connectInfoProcesser(std::function<void(string)> aInfoProcesser);
    void update(double timestep);
    void disconnectInfoProcesser();
    std::string getMobNameToSpawn();

private:

    double period;
    double currentTime;
    size_t waveNumber, waveCount;
    std::function<void(string)> mInfoProcesser;
    std::string previousValue{};
    SpawnStatusT currentSpawnStatus;
    std::vector<std::deque<std::pair<int, std::string>>> waveMobList;
};

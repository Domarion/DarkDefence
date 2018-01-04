#pragma once

#include <string>
#include <utility>
#include <vector>
#include <functional>
#include <deque>

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

    void loadWavesInfo(const std::string& aFilename);
    bool canSpawn(double aTimeStep);
    bool IsReadyForSpawn() const;
    bool noMoreWaves() const;
    double getCurrentTime() const;
    bool isSpawned() const;
    size_t getWaveNumber() const;
    size_t getWaveCount() const;
    void reset();
    void connectInfoProcesser(std::function<void(std::string)> aInfoProcesser);
    void update(double aTimeStep);
    void disconnectInfoProcesser();
    std::string getMobNameToSpawn();

private:

    double period = 5000;
    double currentTime = 5000;

    size_t waveNumber = 0, waveCount = 0;

    std::string previousValue;
    SpawnStatusT currentSpawnStatus = SpawnStatusT::NoSpawn;
    std::vector<std::deque<std::pair<int, std::string>>> waveMobList;

    std::function<void(std::string)> mInfoProcesser;
};

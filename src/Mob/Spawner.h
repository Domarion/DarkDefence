#pragma once

#include "Mob/MobSpawner.h"
#include "Grouping/SceneObject.h"

class Spawner : public SceneObject
{
public:
    Spawner();

    bool update(double timestep) override;
    void doSpawn();
    void connectInfoProcesser(std::function<void(string)> aInfoProcesser);
    void disconnectInfoProcesser();
    void disconnectSpawnCallback();

    void loadWavesInfo(const std::string& aFilePath);
    void connectSpawnCallBack(std::function<void(std::string, Position, size_t)> aCallBack);

private:
    MobSpawner mSpawnerModel;
    int timePeriod;
    int currentTime;
    std::function<void(std::string, Position, size_t)> mSpawnCallBack;
    const size_t mInitialDrawPriority = 2;
    size_t mDrawPriority = 0;
};

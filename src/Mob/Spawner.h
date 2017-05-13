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

    void loadWavesInfo();
    void connectSpawnCallBack(std::function<void(std::string, Position)> aCallBack);

private:
    MobSpawner mSpawnerModel;
    int timePeriod;
    int currentTime;
    std::function<void(std::string, Position)> mSpawnCallBack;
};

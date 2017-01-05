#pragma once
#include "Mob/Mob.h"
#include "Mob/MobSpawner.h"
#include "../GlobalScripts/TileMapManager.h"

class Spawner : public SceneObject
{
public:
    Spawner();
    virtual ~Spawner() = default;
    virtual bool update(double timestep) override;
    void doSpawn(std::shared_ptr<RenderingSystem>& aRenderingContext, std::shared_ptr<TileMapManager> aTileMap);
    void connectInfoProcesser(std::function<void(string)> aInfoProcesser);
    void disconnectInfoProcesser();
    void loadWavesInfo();

private:
    MobSpawner mSpawnerModel;
};

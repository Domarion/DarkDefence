#pragma once
#include "../Grouping/Scene.h"
#include "../MissionSystem/Mission.h"

class MapMenuScene: public Scene
{
public:
    MapMenuScene();
    virtual ~MapMenuScene();
    virtual void init(SceneManager* sceneManagerPtr) override;
    virtual void clear() override;

private:
    void initNavigationButtons();
    void loadMissionView();
    void loadMapPicture();
    void initMapIndicators();

    int currentMissionIndex;
    Mission currentMission;

};

#pragma once
#include "../Grouping/Scene.h"
#include "../MissionSystem/Mission.h"

class MapMenuScene: public Scene
{
public:
    MapMenuScene(std::shared_ptr<RenderingSystem> &aRenderer, std::shared_ptr<InputDispatcher> aInputDispatcher);
    virtual ~MapMenuScene();
    virtual void init(std::shared_ptr<SceneManager> sceneManagerPtr) override;
    virtual void clear() override;

private:
    void initNavigationButtons();
    void loadMissionView();
    void loadMapPicture();
//    void initMapIndicators();

    int currentMissionIndex;
    Mission currentMission;

};

#pragma once

#include "../Grouping/Scene.h"
#include "../MissionSystem/Mission.h"

class MapMenuScene final: public Scene
{
public:
    MapMenuScene(std::shared_ptr<RenderingSystem>& aRenderer, std::shared_ptr<InputDispatcher> aInputDispatcher);

    void init(std::shared_ptr<SceneManager> sceneManagerPtr) override;

private:
    void initNavigationButtons();
    void loadMissionView();
//    void loadMapPicture();
//    void initMapIndicators();

    Mission currentMission;

};

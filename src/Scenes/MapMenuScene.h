#pragma once

#include "../Grouping/Scene.h"
#include "../MissionSystem/Mission.h"

// TODO : Remove
#include "../AudioSystem/Sound.hpp"

class MapMenuScene final: public Scene
{
public:
    MapMenuScene(std::shared_ptr<RenderingSystem>& aRenderer, std::shared_ptr<InputDispatcher> aInputDispatcher);

    void init() override;

private:
    void initNavigationButtons();
    void loadMissionView();
//    void loadMapPicture();
//    void initMapIndicators();

    Mission currentMission;
    Sound testSound;
};

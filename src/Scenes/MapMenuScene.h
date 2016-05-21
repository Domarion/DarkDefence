#pragma once
#include "../Grouping/Scene.h"
#include "../MissionSystem/Mission.h"
#include "../GraphicsSystem/UI/MissionView.h"
#include "../GraphicsSystem/UI/TextButton.h"
#include "../GraphicsSystem/UI/MapIndicator.h"
#include "../GraphicsSystem/CTexture.h"

class MapMenuScene: public Scene
{
public:
    MapMenuScene();
    virtual ~MapMenuScene();
    virtual void initScene(SceneManager* sceneManagerPtr) override;
    virtual void finalizeScene() override;
    virtual void startUpdate(double timestep) override;
    void LoadSceneByName(std::string sceneName);
private:
    Mission currentMission;
    CTexture mapPicture;
    MissionView currentMissionView;
    TextButton loadButton;
    MapIndicator mapIndicator;

};

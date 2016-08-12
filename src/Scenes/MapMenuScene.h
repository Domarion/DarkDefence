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
   // std::shared_ptr<CFont> arialFont;
    Mission currentMission;
    CTexture mapPicture;
    MissionView currentMissionView;
    TextButton loadButton;
    TextButton backButton;
    MapIndicator mapIndicator;


    // Scene interface
public:
    virtual void resetState() override;
};

#pragma once
#include "../Grouping/Scene.h"
#include "../GraphicsSystem/UI/Label.h"
#include "../GraphicsSystem/UI/TextButton.h"
class ScoreScene: public Scene
{
public:
    ScoreScene();
    virtual ~ScoreScene();
    virtual void initScene(SceneManager* sceneManagerPtr) override;
    virtual void finalizeScene() override;
private:
    TTF_Font* arialFont;
    TextButton button;
    Label ScoreLabel;
};


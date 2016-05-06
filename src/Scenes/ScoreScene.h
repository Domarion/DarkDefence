#pragma once
#include "../Grouping/Scene.h"
#include "../GraphicsSystem/UI/CompositeLabel.h"
#include "../GraphicsSystem/UI/TextButton.h"
#include <vector>
using std::vector;

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
    vector< CompositeLabel* > rewardViews;
};


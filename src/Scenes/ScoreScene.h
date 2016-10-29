#pragma once
#include "../Grouping/Scene.h"


class ScoreScene: public Scene
{
public:
    ScoreScene(std::shared_ptr<RenderingSystem> &aRenderer);
    virtual ~ScoreScene();
    virtual void init(std::shared_ptr<SceneManager> sceneManagerPtr) override;
    virtual void clear() override;

private:
    void showItemRewards();
    void showGoldReward();
    void showScoreView();

};


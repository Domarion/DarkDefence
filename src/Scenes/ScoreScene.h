#pragma once
#include "../Grouping/Scene.h"


class ScoreScene: public Scene
{
public:
    ScoreScene();
    virtual ~ScoreScene();
    virtual void init(SceneManager* sceneManagerPtr) override;
    virtual void clear() override;

private:
    void initControlLabel();
    void showItemRewards();
    void showGoldReward();
    void showScoreView();

};


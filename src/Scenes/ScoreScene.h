#pragma once

#include "../Grouping/Scene.h"

class ScoreScene: public Scene
{
public:

    ScoreScene(std::shared_ptr<RenderingSystem>& aRenderer, std::shared_ptr<InputDispatcher> aInputDispatcher);

    virtual void init() override;
    virtual void clear() override;

private:

    void showItemRewards();
    void showGoldReward();
    void showScoreView();
};


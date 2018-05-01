#pragma once

#include <functional>

#include "../Grouping/Scene.h"

class MainScene: public Scene
{
public:

    MainScene(std::shared_ptr<RenderingSystem>& aRenderer, std::shared_ptr<InputDispatcher> aInputDispatcher);

    virtual void init() override;
    void ConnectMethod(std::function<void(string)> handler);

private:

    void loadMenuItems(const std::string& aFilename);
    void initUIMenuItems();
    void initBackground();

    vector<pair<string, string>> itemNamesSceneNamesMapping;
    std::function<void(string)> method;
};



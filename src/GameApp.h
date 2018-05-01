#pragma once

#include "Grouping/SceneManager.h"
#include "Input/InputDispatcher.h"

class RenderingSystem;

class GameApp final
{
public:

    explicit GameApp(Size aWindowSize);

    GameApp(const GameApp&) = delete;
    GameApp& operator=(const GameApp&) = delete;

    void initLibrary(int windowWidth, int windowHeight);
    void preloadData();
    void addScenes();
    int gameLoop();

    void receiveMessage(std::string msg);

private:

    void pause();
    void unpause();
    bool processInput();
    void renderScene();
    bool isPaused();

    SDL_Event event;
    std::shared_ptr<RenderingSystem> mRenderer;
    SceneManager mSceneManager;
    std::shared_ptr<InputDispatcher> mInputDispatcher;

    bool mIsPaused = false;
    bool mNeedQuit = false;
};

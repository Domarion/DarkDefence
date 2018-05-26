#include "SDL_Engine.h"
#include "GameApp.h"

int main(int /*argc*/, char** /*args*/)
{
    SDL2Engine::SDL2 library(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    Size screenSize = library.getScreenResolution();
    screenSize.height -= 50;//TODO: убрать

    GameApp app(screenSize);
    app.preloadData();
    app.addScenes();

    return app.gameLoop();
}



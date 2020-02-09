#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "SDL_Engine.h"
#include <Logging/Logger.h>

namespace SDL2Engine
{

SDL2::SDL2(uint32_t flags)
{
    SDL_SetMainReady();
    if (SDL_Init(flags) == 0)
    {
        int imgFlags = IMG_INIT_PNG;
        int initResult = IMG_Init(imgFlags);
        if ((initResult & imgFlags) != imgFlags)
        {
            LOG_ERROR(std::string(IMG_GetError()));
        }

        if (TTF_Init() != 0)
        {
            LOG_ERROR(std::string(TTF_GetError()));
        }

        // Flag for separate mouse and touch handle
//        SDL_SetHint(SDL_HINT_ANDROID_SEPARATE_MOUSE_AND_TOUCH, "1");

        return;
    }

    LOG_ERROR(std::string(SDL_GetError()));
}

Size SDL2::getScreenResolution() const
{
    Size resolution;

    SDL_DisplayMode dm;

    if (SDL_GetDesktopDisplayMode(0, &dm) == 0)
    {
        resolution.width = dm.w;
        resolution.height = dm.h;
    }
    return resolution;

}

SDL2::~SDL2()
{
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

}


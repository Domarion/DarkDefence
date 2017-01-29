#include "SDL_Engine.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

namespace SDL2Engine
{
SDL2::SDL2(uint32_t flags)
{
    if (SDL_Init(flags) == 0)
    {
        int imgFlags = IMG_INIT_PNG;
        IMG_Init(imgFlags);
        TTF_Init();
        // Flag for separate mouse and touch handle
        SDL_SetHint(SDL_HINT_ANDROID_SEPARATE_MOUSE_AND_TOUCH, "1");
    }
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


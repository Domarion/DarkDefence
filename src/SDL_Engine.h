#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "GraphicsSystem/newSystem/UtilityStructs.h"
namespace SDL2Engine
{
    class SDL2 final
    {
    public:
        explicit SDL2(Uint32 flags)
        {
            if (SDL_Init(flags) == 0)
            {
                int imgFlags = IMG_INIT_PNG;
                IMG_Init(imgFlags);
                TTF_Init();
            }
        }

        Size getScreenResolution() const
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

        SDL2() = delete;

        ~SDL2()
        {
            TTF_Quit();
            IMG_Quit();
            SDL_Quit();
        }
    };


}

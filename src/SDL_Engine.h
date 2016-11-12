#pragma once
#include <SDL_stdinc.h>
#include "GraphicsSystem/newSystem/UtilityStructs.h"
namespace SDL2Engine
{
    class SDL2 final
    {
    public:
        explicit SDL2(Uint32 flags);

        Size getScreenResolution() const;

        SDL2() = delete;

        ~SDL2();
    };


}

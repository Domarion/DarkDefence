#pragma once

#include "GraphicsSystem/newSystem/UtilityStructs.h"

namespace SDL2Engine
{

class SDL2 final
{
public:
    explicit SDL2(uint32_t flags);

    Size getScreenResolution() const;

    SDL2() = delete;

    ~SDL2();
};

}

#pragma once

#include <cstdint>

#include "GraphicsSystem/newSystem/Size.h"

namespace SDL2Engine
{

class SDL2 final
{
public:
    explicit SDL2(uint32_t aSubsystemsFlags);

    Size getScreenResolution() const;

    ~SDL2();
};

}

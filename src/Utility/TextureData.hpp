#pragma once

#include <cereal/access.hpp>
#include <cereal/types/string.hpp>
#include "GraphicsSystem/newSystem/UtilityStructs.h"

namespace UtilityStruct
{
struct Res
{
    Res() = default;
    ~Res() = default;

    std::string Caption;
    Size ImageSize;
    std::string ImagePath;
private:
    friend class cereal::access;
    template <typename Archive>
    void serialize(Archive &ar, const unsigned int /*version*/)
    {
        ar(Caption, ImageSize.width, ImageSize.height, ImagePath);
    }
};
} 

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
    std::string AnimationPackPath;
private:
    friend class cereal::access;
    template <typename Archive>
    void serialize(Archive &ar, const unsigned int /*version*/)
    {
        ar(
           CEREAL_NVP(Caption),
           cereal::make_nvp("ImageWidth", ImageSize.width),
           cereal::make_nvp("ImageHeight", ImageSize.height),
           CEREAL_NVP(ImagePath),
           CEREAL_NVP(AnimationPackPath));

    }
};
} 

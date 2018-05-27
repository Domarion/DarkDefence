#pragma once

#include <cereal/access.hpp>
#include <cereal/types/string.hpp>

#include "GraphicsSystem/newSystem/UtilityStructs.h"

namespace UtilityStruct
{

struct Res
{
    std::string Caption;
    Size ImageSize;
    std::string ImagePath;
    std::string AnimationPackPath;

private:
    friend class cereal::access;
    template <typename Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar(
            CEREAL_NVP(Caption),
            cereal::make_nvp("ImageWidth", ImageSize.width),
            cereal::make_nvp("ImageHeight", ImageSize.height),
            CEREAL_NVP(ImagePath),
            CEREAL_NVP(AnimationPackPath));
    }
};

struct ResAudio
{
    std::string Caption;
    std::string Path;
    enum class TAudioType : bool
    {
        Sound = 0,
        Music = 1
    };
    TAudioType AudioType = TAudioType::Sound;

private:
    friend class cereal::access;
    template <typename Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar(
            CEREAL_NVP(Caption),
            CEREAL_NVP(Path),
            CEREAL_NVP(AudioType));
    }
};

}

#pragma once
#include <cereal/access.hpp>
#include <cereal/types/string.hpp>
#include "Enums.h"
#include "GraphicsSystem/newSystem/UtilityStructs.h"

struct StructureData
{
private:
    friend class cereal::access;
    template <typename Archive>
    void serialize(Archive &ar, const unsigned int /*version*/)
    {
        ar(cereal::make_nvp("Name", Name),
           cereal::make_nvp("Width", ImageSize.width),
           cereal::make_nvp("Height", ImageSize.height),
           cereal::make_nvp("PositionX", ImagePosition.x),
           cereal::make_nvp("PositionY", ImagePosition.y),
           cereal::make_nvp("XAnchorPlace", xCoordAnchorType),
           cereal::make_nvp("YAnchorPlace", yCoordAnchorType));

    }
public:
    std::string Name{};
    Size ImageSize{};
    Position ImagePosition{};
    Enums::AnchorCoordTypes xCoordAnchorType = Enums::AnchorCoordTypes::Min;
    Enums::AnchorCoordTypes yCoordAnchorType = Enums::AnchorCoordTypes::Min;

}; 

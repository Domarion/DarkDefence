#pragma once

#include <cereal/access.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>

#include "HeroInventory.h"
#include "../GraphicsSystem/newSystem/ConcreteUIViews/UISlotContainer.h"

template<class Archive>
void serialize(Archive& archive,
          Size& aSize)
{
    archive(cereal::make_nvp("Width", aSize.width), cereal::make_nvp("Height", aSize.height));
}

template<class Archive>
void serialize(Archive& archive,
          Position& aPosition)
{
    archive(cereal::make_nvp("X", aPosition.x), cereal::make_nvp("Y", aPosition.y));
}

struct SlotConfig
{
private:
    friend class cereal::access;
    template <typename Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar(
            cereal::make_nvp("ItemsCount", ItemsCount),
            cereal::make_nvp("ItemSize", ItemSize),
            cereal::make_nvp("ItemPositions", ItemsPositions),
            cereal::make_nvp("BackImagePath", EmptyImagePath));
    }

public:
    size_t ItemsCount = 0;
    Size ItemSize;
    std::vector<Position> ItemsPositions;
    std::string EmptyImagePath;
};

class HeroInventoryController final
{
public:

    void initView(std::shared_ptr<RenderingSystem>& aRenderer, const std::string& aConfPath);
    void initLocalPositions(Size aRectSize);

    void setView(const std::shared_ptr<UISlotContainer>& aNewView);
    const std::shared_ptr<UISlotContainer>& getView() const;

    void setModel(const std::shared_ptr<HeroInventory>& aNewModel);
    const std::shared_ptr<HeroInventory>& getModel() const;

    void receiveItemFromModel(std::string aCaption, size_t aItemType);

private:

    std::shared_ptr<HeroInventory> mModel;
    std::shared_ptr<UISlotContainer> mView;
    std::vector<Position> mSlotsPositions;
};



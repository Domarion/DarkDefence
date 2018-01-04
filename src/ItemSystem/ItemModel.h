#pragma once

#include <cereal/access.hpp>
#include <cereal/types/string.hpp>
#include "../Enums.h"

class ItemModel
{
    friend class cereal::access;
    template <typename Archive>
    void serialize(Archive& ar)
    {
        ar(CEREAL_NVP(caption), CEREAL_NVP(description), CEREAL_NVP(itemType), CEREAL_NVP(price));
    }
public:
    ItemModel() = default;
    ItemModel(const std::string& aCaption, const std::string& aDescription, Enums::ItemTypes aItemType, int aPrice);

    const std::string& getDescription() const;
    void setDescription(const std::string& aDescription);

    Enums::ItemTypes getItemType() const;
    void setItemType(Enums::ItemTypes aItemType);

    int getPrice() const;
    void setPrice(int aPrice);

    void clean();
    void safeClean();

    const std::string& getCaption() const;
    void setCaption(const std::string& aCaption);

private:
    std::string caption;
    std::string description;
    Enums::ItemTypes itemType;
    int price = 0;
};

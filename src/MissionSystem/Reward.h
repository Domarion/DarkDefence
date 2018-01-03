#pragma once

#include <cereal/access.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/list.hpp>

class Reward
{
     friend class cereal::access;
     template <typename Archive>
     void serialize(Archive &ar, const unsigned int /*version*/)
     {
         ar(
            cereal::make_nvp("ItemNames", mItemNames),
            cereal::make_nvp("CoinsAmount", mCoinsAmount));
     }

public:

    Reward() = default;
    explicit Reward(int aCoinsAmount);

    void addItemName(const std::string& aItemName);
    void setGoldCoins(int aCoinsAmount);
    int getGoldCoins() const;

    const std::list<std::string>& getFullDescription() const;

private:
    std::list<std::string> mItemNames;
    int mCoinsAmount = 0;
};


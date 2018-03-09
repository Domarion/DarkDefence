#pragma once

#include <string>

#include <cereal/access.hpp>
#include <cereal/types/string.hpp>

#include "../Enums.h"

using std::string;
using Enums::EReaction;

class EnemyInfo
{
    friend class cereal::access;
    template <typename Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar(cereal::make_nvp("enemyTag", tag),
           cereal::make_nvp("enemyReaction", reaction),
           cereal::make_nvp("priority", priority));
    }

public:
    EnemyInfo() = default;
    EnemyInfo(const string& aTag, EReaction aReaction, int aPriority);

    const std::string& getTag() const;
    void setTag(const string& aTag);

    EReaction getReaction() const;
    void setReaction(Enums::EReaction aReaction);

    int getPriority() const;
    void setPriority(int aPriority);

private:
    string tag;
    EReaction reaction = Enums::EReaction::Attack;
    int priority = 0;
};

#pragma once
#include <string>
using std::string;

#include "../Enums.h"
using Enums::EReaction;

#include <cereal/access.hpp>
#include <cereal/types/string.hpp>

class EnemyInfo
{
    friend class cereal::access;
    template <typename Archive>
      void serialize(Archive &ar, const unsigned int /*version*/)
    {
        ar(cereal::make_nvp("enemyTag", tag),
           cereal::make_nvp("enemyReaction", reaction),
           cereal::make_nvp("priority", priority));
    }

public:
    EnemyInfo();
    EnemyInfo(const string& aTag, EReaction aReaction, int aPriority);

    string getTag() const;
    void setTag(const string &value);

    EReaction getReaction() const;
    void setReaction(const EReaction &value);

    int getPriority() const;
    void setPriority(int value);

private:
    string tag;
    EReaction reaction;
    int priority;
};

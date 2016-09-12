#pragma once
#include <string>
using std::string;

#include "../Enums.h"
using Enums::EReaction;

#include <boost/serialization/access.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/nvp.hpp>
class EnemyInfo
{
    friend class boost::serialization::access;
    template <typename Archive>
      void serialize(Archive &ar, const unsigned int version)
    {
        ar & boost::serialization::make_nvp("enemyTag", tag);
        ar & boost::serialization::make_nvp("enemyReaction", reaction);
        ar & boost::serialization::make_nvp("priority", priority);
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

#pragma once
#include "../GlobalScripts/GameModel.h"
#include "BasicGoal.h"
#include "../Enums.h"
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

class ResourceGoal: public BasicGoal
{
    friend class boost::serialization::access;
    template <typename Archive>
      void serialize(Archive &ar, const unsigned int version)
    {
        ar & boost::serialization::make_nvp("BasicGoal", (boost::serialization::base_object<BasicGoal>(*this)));
        ar & BOOST_SERIALIZATION_NVP(resourceType);

    }

public:
    ResourceGoal();
    ResourceGoal(std::string aDescription, int controlNumber, Enums::ResourceTypes aResourceType);
    void setResourceType(Enums::ResourceTypes resType);
    virtual bool checkCondition() override;
    Enums::ResourceTypes getResourceType();
private:
    Enums::ResourceTypes resourceType;
};


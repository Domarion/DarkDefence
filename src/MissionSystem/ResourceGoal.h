#pragma once

#include "BasicGoal.h"
#include "Enums.h"
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/base_class.hpp>
#include "GlobalScripts/ResourcesModel.h"
class ResourceGoal: public BasicGoal
{
    friend class cereal::access;
    template <typename Archive>
    void serialize(Archive &ar)
    {
        ar(cereal::base_class<BasicGoal>(this), CEREAL_NVP(resourceType));
    }

public:
    ResourceGoal();
    ResourceGoal(std::string aDescription,
                 int controlNumber,
                 Enums::ResourceTypes aResourceType,
                 std::shared_ptr<ResourcesModel> aResourceModel = nullptr);
    void setResourceModel(std::shared_ptr<ResourcesModel> aResourceModel);
    void setResourceType(Enums::ResourceTypes resType);
    virtual bool checkCondition(Enums::GameStatuses aGameStatus) override;
    Enums::ResourceTypes getResourceType();
private:
    int getResourceAmount();
    Enums::ResourceTypes resourceType;
    std::shared_ptr<ResourcesModel> resourceModel; //TODO: Передавать ResourcesModel сюда, иначе не будет работать
};

CEREAL_REGISTER_TYPE(ResourceGoal)
CEREAL_REGISTER_POLYMORPHIC_RELATION(BasicGoal, ResourceGoal)

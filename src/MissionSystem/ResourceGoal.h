#pragma once

#include "BasicGoal.h"
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/base_class.hpp>
#include "GlobalScripts/ResourcesModel.h"

class ResourceGoal: public BasicGoal
{
    friend class cereal::access;
    template <typename Archive>
    void serialize(Archive &ar)
    {
        ar(cereal::base_class<BasicGoal>(this), cereal::make_nvp("ResourceType", mResourceType));
    }

public:
    ResourceGoal() = default;
    ResourceGoal(
        const std::string& aDescription,
        int aControlNumber,
        Enums::ResourceTypes aResourceType);

    void setResourceModel(const std::shared_ptr<ResourcesModel>& aResourceModel);
    void setResourceType(Enums::ResourceTypes aResType);

    virtual bool checkCondition(Enums::GameStatuses aGameStatus) override;

    Enums::ResourceTypes getResourceType() const;

private:

    int getResourceAmount() const;
    Enums::ResourceTypes mResourceType = Enums::ResourceTypes::UNKNOWN;
    std::shared_ptr<ResourcesModel> mResourceModel; //TODO: Передавать ResourcesModel сюда, иначе не будет работать
};

CEREAL_REGISTER_TYPE(ResourceGoal)
CEREAL_REGISTER_POLYMORPHIC_RELATION(BasicGoal, ResourceGoal)

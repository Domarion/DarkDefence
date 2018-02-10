/*
 * MineModel.h
 *
 *  Created on: 14 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once

#include "DestructibleObject.h"
#include <cereal/types/base_class.hpp>
#include "../Enums.h"
#include "GlobalScripts/ResourcesModel.h"
using std::pair;

class MineModel: public DestructibleObject
{
    friend class cereal::access;
    template <typename Archive>
    void serialize(Archive &ar)
    {

       ar(
           cereal::base_class<DestructibleObject>(this),
           CEREAL_NVP(productionType),
           CEREAL_NVP(production),
           CEREAL_NVP(productionPeriod),
           cereal::make_nvp("DestructionLoss", mDestructionLoss));

        currentTime = productionPeriod.first;
    }

public:

    MineModel() = default;
    MineModel(
        const std::string& aName,
        const std::string& aTag,
        int aMaxHealth,
        std::array<int, GlobalConstants::damageTypeCount>& aProtection,
        Enums::ResourceTypes aResType,
        int aProduction,
        double aPeriod,
        int aDestructionLoss);
    MineModel(const MineModel& aRight);

    int getLimit() const;
    int calculateLimitAfterDestruction() const;
    void setLimit(int aLimit);
    int getProduction() const;
    void setProduction(int aProduction);
    double getProductionPeriod() const;
    void setProductionPeriod(double aProductionPeriod);
	double getCurrentTime() const;
    void setCurrentTime(double aCurrentTime);
    Enums::ResourceTypes getProductionType() const;
    size_t getProductionTypeIndex() const;

    void produce(double aTimeStep, const std::shared_ptr<ResourcesModel>& aResourceModel);

private:

    pair<int, int> production{};
    pair<double, double> productionPeriod{};
    double currentTime = 0;
    Enums::ResourceTypes productionType = Enums::ResourceTypes::WHEAT;
    int mDestructionLoss = 100;
    pair<int, int> limit{};


};


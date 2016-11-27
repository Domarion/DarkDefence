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

       ar(cereal::base_class<DestructibleObject>(this), productionType, production, productionPeriod);

        currentTime = productionPeriod.first;
    }



public:
	MineModel();
    MineModel(string aName, string aTag,
              int aMaxHealth, int aProtection[], Enums::ResourceTypes resType, int aProduction, double aPeriod);
	~MineModel();
    MineModel(const MineModel& right);
    int getLimit() const;
    void setLimit(int aLimit);
    int getProduction() const;
    void setProduction(int aProduction);
    double getProductionPeriod() const;
    void setProductionPeriod(double aProductionPeriod);
	double getCurrentTime() const;
    void setCurrentTime(double aCurrentTime);
    Enums::ResourceTypes getProductionType() const;

    void produce(double timestep, std::shared_ptr<ResourcesModel> aResourceModel);
private:
	pair<int, int> limit;
	pair<int, int> production;
	pair<double, double> productionPeriod;
	double currentTime;
	Enums::ResourceTypes productionType;


};


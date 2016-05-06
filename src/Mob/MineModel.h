/*
 * MineModel.h
 *
 *  Created on: 14 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once

#include "DestructibleObject.h"
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>
#include "../Enums.h"
using std::pair;

class MineModel: public DestructibleObject
{
    friend class boost::serialization::access;
    template <typename Archive>
      void serialize(Archive &ar, const unsigned int version)
    {

        //ar.template register_type<MobModel>();
        ar & boost::serialization::make_nvp("DestructibleObject", (boost::serialization::base_object<DestructibleObject>(*this)));
        //ar & attackDamage;
        ar & BOOST_SERIALIZATION_NVP(productionType);
        ar & BOOST_SERIALIZATION_NVP(production);
        ar & BOOST_SERIALIZATION_NVP(productionPeriod);

        currentTime = productionPeriod.first;
    }



public:
	MineModel();
    MineModel(string aName, string aTag,
              int aMaxHealth, int aProtection[], Enums::ResourceTypes resType, int aProduction, double aPeriod);
	~MineModel();
    MineModel(const MineModel& right);
    int getLimit() const;
    void setLimit(int limit);
    int getProduction() const;
    void setProduction(int production);
    double getProductionPeriod() const;
    void setProductionPeriod(double productionPeriod);
	double getCurrentTime() const;
	void setCurrentTime(double currentTime);
    Enums::ResourceTypes getProductionType() const;

    void produce(double timestep);
private:
	pair<int, int> limit;
	pair<int, int> production;
	pair<double, double> productionPeriod;
	double currentTime;
	Enums::ResourceTypes productionType;


};


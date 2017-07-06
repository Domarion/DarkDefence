/*
 * MineModel.cpp
 *
 *  Created on: 14 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "MineModel.h"

MineModel::MineModel()
    : DestructibleObject(),limit(0, 0)
    , production(0, 0)
    , productionPeriod(0, 0)
    , currentTime(0.0)
    , productionType(Enums::ResourceTypes::WHEAT)
{
	// TODO Auto-generated constructor stub

}

MineModel::MineModel(string aName, string aTag, int aMaxHealth, int aProtection[], Enums::ResourceTypes resType, int aProduction, double aPeriod)
    : DestructibleObject(aName, aTag, aMaxHealth, aProtection)
    , limit(0, 0)
    , production(0, 0)
    , productionPeriod(0, 0)
    , currentTime(0.0)
    , productionType(resType)
{
    production.first = aProduction;
    production.second = 0;

    productionPeriod.first = aPeriod;
    productionPeriod.second = 0;
    currentTime = aPeriod;
}

MineModel::~MineModel()
{
    // TODO Auto-generated destructor stub
}

MineModel::MineModel(const MineModel &right)
    :DestructibleObject(right)
{
    productionType = right.productionType;
    production = right.production;
    limit = right.limit;
    productionPeriod = right.productionPeriod;
    currentTime = productionPeriod.first;
}


int MineModel::getLimit() const
{
    return limit.first + limit.second;
}

int MineModel::getProduction() const
{
    return production.first + production.second;
}

void MineModel::setProduction(int aProduction)
{
    this->production.first = aProduction;
}

double MineModel::getProductionPeriod() const
{
    return productionPeriod.first + productionPeriod.second;
}

double MineModel::getCurrentTime() const
{
	return currentTime;
}

void MineModel::setCurrentTime(double aCurrentTime)
{
    this->currentTime = aCurrentTime;
}

Enums::ResourceTypes MineModel::getProductionType() const
{
    return productionType;
}

size_t MineModel::getProductionTypeIndex() const
{
    return Enums::toIntegralType(productionType);
}

void MineModel::produce(double timestep, std::shared_ptr<ResourcesModel> aResourceModel)
{
    if (currentTime <= 0)
    {
        int prod = getProduction();
        std::cout << "Prod =" << (prod) <<std::endl;
        if ( prod <= getLimit() && aResourceModel->addResource(static_cast<int>(productionType), prod))
        {
             std::cout << "Prod++ =" << (prod) <<std::endl;
            limit.first -= prod;
        }

        currentTime = getProductionPeriod();
    }
    else
        currentTime -= timestep;
}

void MineModel::setProductionPeriod(double aProductionPeriod)
{
    this->productionPeriod.first = aProductionPeriod;
    setCurrentTime( getProductionPeriod());
}

void MineModel::setLimit(int aLimit)
{
    this->limit.first = aLimit;
}



/*
 * MineModel.cpp
 *
 *  Created on: 14 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "MineModel.h"

MineModel::MineModel(
    const std::string& aName,
    const std::string& aTag,
    int aMaxHealth,
    std::array<int, GlobalConstants::damageTypeCount>& aProtection,
    Enums::ResourceTypes aResType,
    int aProduction,
    double aPeriod)
    : DestructibleObject(aName, aTag, aMaxHealth, aProtection)
    , production{aProduction, 0}
    , productionPeriod{aPeriod, 0}
    , currentTime(aPeriod)
    , productionType(aResType)
{
}

MineModel::MineModel(const MineModel& aRight)
    : DestructibleObject(aRight)
{
    productionType = aRight.productionType;
    production = aRight.production;
    limit = aRight.limit;
    productionPeriod = aRight.productionPeriod;
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

void MineModel::produce(double aTimeStep, const std::shared_ptr<ResourcesModel>& aResourceModel)
{
    if (currentTime <= 0)
    {
        int prod = getProduction();
        if ( prod <= getLimit() && aResourceModel->addResource(productionType, prod))
        {
            limit.first -= prod;
        }

        currentTime = getProductionPeriod();
    }
    else
        currentTime -= aTimeStep;
}

void MineModel::setProductionPeriod(double aProductionPeriod)
{
    productionPeriod.first = aProductionPeriod;
    setCurrentTime(getProductionPeriod());
}

void MineModel::setLimit(int aLimit)
{
    limit.first = aLimit;
}



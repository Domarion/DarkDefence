/*
 * MineModel.cpp
 *
 *  Created on: 14 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "MineModel.h"
#include "../GlobalScripts/GameModel.h"
MineModel::MineModel()
{
	// TODO Auto-generated constructor stub

}

MineModel::MineModel(string aName, string aTag, int aMaxHealth, int aProtection[], Enums::ResourceTypes resType, int aProduction, double aPeriod)
:DestructibleObject(aName, aTag, aMaxHealth, aProtection), productionType(resType)
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
{
    name = right.name;
    tag = right.tag;
    maximumHealth = right.maximumHealth;
    currentHealth = right.currentHealth;
    for(int i = 0; i < DestructibleObject::damageTypesCount; ++i)
        attackProtection[i] = right.attackProtection[i];

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

void MineModel::setProduction(int production)
{
    this->production.first = production;
}

double MineModel::getProductionPeriod() const
{
    return productionPeriod.first + productionPeriod.second;
}

double MineModel::getCurrentTime() const
{
	return currentTime;
}

void MineModel::setCurrentTime(double currentTime)
{
    this->currentTime = currentTime;
}

Enums::ResourceTypes MineModel::getProductionType() const
{
    return productionType;
}

void MineModel::produce(double timestep)
{
    if (currentTime <= 0)
    {
        int prod = getProduction();
        std::cout << "Prod =" << (prod) <<std::endl;
        if ( prod <= getLimit() && GameModel::getInstance()->getResourcesModel()->addResource(productionType, prod))
        {
             std::cout << "Prod++ =" << (prod) <<std::endl;
            limit.first -= prod;
        }

        currentTime = getProductionPeriod();
    }
    else
        currentTime -= timestep;
}

void MineModel::setProductionPeriod(double productionPeriod)
{
    this->productionPeriod.first = productionPeriod;
    setCurrentTime( getProductionPeriod());
}

void MineModel::setLimit(int limit)
{
    this->limit.first = limit;
}



/*
 * MineModel.cpp
 *
 *  Created on: 14 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "MineModel.h"

MineModel::MineModel()
{
	// TODO Auto-generated constructor stub

}

MineModel::~MineModel()
{
	// TODO Auto-generated destructor stub
}


pair<int, int> MineModel::getLimit() const
{
	return limit;
}

pair<int, int> MineModel::getProduction() const
{
	return production;
}

void MineModel::setProduction(pair<int, int> production)
{
	this->production = production;
}

const pair<double, double>& MineModel::getProductionPeriod() const
{
	return productionPeriod;
}

double MineModel::getCurrentTime() const
{
	return currentTime;
}

void MineModel::setCurrentTime(double currentTime)
{
	this->currentTime = currentTime;
}

void MineModel::setProductionPeriod(const pair<double, double>& productionPeriod)
{
	this->productionPeriod = productionPeriod;
}

void MineModel::setLimit(pair<int, int> limit)
{
	this->limit = limit;
}



/*
 * MineModel.h
 *
 *  Created on: 14 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include <string>
#include "DestructibleObject.h"
using std::pair;
#include "../Enums.h"

class MineModel: public DestructibleObject
{
public:
	MineModel();
	~MineModel();

	pair<int, int> getLimit() const;
	void setLimit(pair<int, int> limit);
	pair<int, int> getProduction() const;
	void setProduction(pair<int, int> production);
	const pair<double, double>& getProductionPeriod() const;
	void setProductionPeriod(const pair<double, double>& productionPeriod);
	double getCurrentTime() const;
	void setCurrentTime(double currentTime);

private:
	pair<int, int> limit;
	pair<int, int> production;
	pair<double, double> productionPeriod;
	double currentTime;
	Enums::ResourceTypes productionType;


};


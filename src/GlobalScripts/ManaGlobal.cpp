/*
 * ManaGlobal.cpp
 *
 *  Created on: 8 марта 2016 г.
 *      Author: kostya_hm
 */

#include "ManaGlobal.h"

ManaGlobal::ManaGlobal()
{
	// TODO Auto-generated constructor stub

}

ManaGlobal::~ManaGlobal()
{
	// TODO Auto-generated destructor stub
}

void ManaGlobal::setCurrent(int value)
{
	if (value > getLimit())
	{
		current = getLimit();
	}
	else
		current = value > 0 ? value : 0;
}

int ManaGlobal::getCurrent() const
{
	return current;
}

void ManaGlobal::setLimit(int value)
{
	limit = value > 0 ? value : 0;
}

int ManaGlobal::getLimit() const
{
	return limit;
}

void ManaGlobal::setRegenValue(int value)
{
	regenerationValue = value;
}

int ManaGlobal::getRegenValue() const
{
	return regenerationValue;
}

void ManaGlobal::setRegenPeriod(double value)//TODO: EPSILON
{
	regenerationPeriod = value > 0.0 ? value : 0.0;
}

double ManaGlobal::getRegenPeriod() const
{
	return regenerationPeriod;
}

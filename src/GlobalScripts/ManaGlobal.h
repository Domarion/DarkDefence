/*
 * ManaGlobal.h
 *
 *  Created on: 8 марта 2016 г.
 *      Author: kostya_hm
 */

#pragma once

class ManaGlobal
{
public:
	ManaGlobal();
	~ManaGlobal();
	void setCurrent(int value);
	int getCurrent() const;
	void setLimit(int value);
	int getLimit() const;
	void setRegenValue(int value);
	int getRegenValue() const;
	void setRegenPeriod(double value);
	double getRegenPeriod() const;

private:
	int current, limit;
	int regenerationValue;
	double regenerationPeriod;


};

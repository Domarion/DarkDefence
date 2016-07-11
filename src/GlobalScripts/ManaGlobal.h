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
    ManaGlobal(int maxMana = 100, int regenValue = 10, double regenPeriod = 2000);
	~ManaGlobal();
	void setCurrent(int value);
	int getCurrent() const;
	void setLimit(int value);
	int getLimit() const;
	void setRegenValue(int value);
	int getRegenValue() const;
	void setRegenPeriod(double value);
	double getRegenPeriod() const;
    bool payMana(int amount);
    void regenerate(double timestep);

private:
    int limit, current;
	int regenerationValue;
	double regenerationPeriod;

};

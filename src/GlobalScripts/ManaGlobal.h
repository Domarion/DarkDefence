#pragma once

class ManaGlobal
{
public:
    ManaGlobal(int maxMana = 100, int regenValue = 50, double regenPeriod = 2000);

	void setCurrent(int value);
	int getCurrent() const;

	void setLimit(int value);
	int getLimit() const;

	void setRegenValue(int value);
	int getRegenValue() const;

	void setRegenPeriod(double value);
	double getRegenPeriod() const;
    bool payMana(int aAmount);

    void regenerate(double aTimeStep);

private:

    int limit = 0, current = 0;
    int regenerationValue = 0;
    double regenerationPeriod = 0;
    double counter = 0;
};

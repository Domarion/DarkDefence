/*
 * ResourceInfo.h
 *
 *  Created on: 15 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include <string>

class ResourceInfo
{
public:
	ResourceInfo();
	~ResourceInfo();
	bool addResource(int amount);
	bool removeResource(int amount);
	void increaseLimit(int amount);
	void decreaseLimit(int amount);
	const std::string& getCaption() const;
	void setCaption(const std::string& caption);
	int getCurrentAmount() const;
	void setCurrentAmount(int value);
	int getLimit() const;
	void setLimit(int value);
	std::string printToString() const;

private:
	int currentAmount, limit;
	std::string caption; 
};

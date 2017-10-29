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

    bool addResource(int aAmount);
    bool removeResource(int aAmount);
    void increaseLimit(int aAmount);
    void decreaseLimit(int aAmount);
	const std::string& getCaption() const;
    void setCaption(const std::string& aCaption);
	int getCurrentAmount() const;
    void setCurrentAmount(int aCurrentAmount);
	int getLimit() const;
    void setLimit(int aLimitAmount);
	std::string printToString() const;

private:
    int currentAmount = 0;
    int limit = 0;
    std::string caption;
};

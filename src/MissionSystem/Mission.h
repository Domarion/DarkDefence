/*
 * Mission.h
 *
 *  Created on: 8 марта 2016 г.
 *      Author: kostya_hm
 */

#pragma once

#include "BasicGoal.h"
#include "Reward.h"
#include <list>
#include <string>

enum MissionStatuses
{
	mNOT_STARTED,
	mIN_PROGRESS,
	mCOMPLETED,
	mFAILED
};

class Mission
{
public:
	Mission();
	~Mission();
	std::string getCaption() const;
	void setCaption(std::string value);
	std::string getDescription() const;
	void setDescription(std::string value);
	MissionStatuses getStatus() const;
	void setStatus(MissionStatuses value);

private:
	std::string caption;
	std::string description;
	std::list<BasicGoal> goals;
	MissionStatuses status;

};



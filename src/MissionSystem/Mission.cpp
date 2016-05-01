/*
 * Mission.cpp
 *
 *  Created on: 8 марта 2016 г.
 *      Author: kostya_hm
 */

#include "Mission.h"

Mission::Mission()
{
	// TODO Auto-generated constructor stub

}

Mission::~Mission()
{
	// TODO Auto-generated destructor stub
}

std::string Mission::getCaption() const
{
	return caption;
}

void Mission::setCaption(std::string value)
{
	caption = value;
}

std::string Mission::getDescription() const
{
	return description;
}

void Mission::setDescription(std::string value)
{
	description = value;
}

MissionStatuses Mission::getStatus() const
{
	return status;
}

void Mission::setStatus(MissionStatuses value)
{
	status = value;
}

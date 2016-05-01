/*
 * StorageModel.cpp
 *
 *  Created on: 14 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "StorageModel.h"

StorageModel::StorageModel()
{
	// TODO Auto-generated constructor stub

}

StorageModel::~StorageModel()
{
	// TODO Auto-generated destructor stub
}



pair<int, int> StorageModel::getLimit() const
{
	return limit;
}

void StorageModel::setLimit(pair<int, int> limit)
{
	this->limit = limit;
}


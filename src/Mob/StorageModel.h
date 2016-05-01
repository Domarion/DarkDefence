/*
 * StorageModel.h
 *
 *  Created on: 14 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include <string>
#include "DestructibleObject.h"
using std::pair;

class StorageModel: public DestructibleObject
{
public:
	StorageModel();
	~StorageModel();
	pair<int, int> getLimit() const;
	void setLimit(pair<int, int> limit);

protected:
	pair<int, int> limit;
};


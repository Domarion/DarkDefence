/*
 * ItemCell.h
 *
 *  Created on: 15 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once

#include "ItemModel.h"
#include "../GraphicsSystem/UI/TextButton.h"

class ItemCell
{
public:
	ItemCell();
	~ItemCell();
private:
	ItemModel* model;
	TextButton* view;
};

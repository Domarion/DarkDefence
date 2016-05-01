/*
 * Terrain.h
 *
 *  Created on: 10 марта 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include "Tile.h"

class Terrain
{
public:
	Terrain(int rows, int columns);
	void fillTerrain();
	~Terrain();
private:
	Tile TileFirst;
	Tile** grid;
	int rows_; int columns_;
};



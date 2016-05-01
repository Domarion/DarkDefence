/*
 * Terrain.cpp
 *
 *  Created on: 10 марта 2016 г.
 *      Author: kostya_hm
 */

#include "Terrain.h"
#include "Tile.h"

Terrain::Terrain(int rows, int columns)
{
	rows_ = rows;
	columns_ = columns;

	grid = new Tile*[rows_];
	for(int i = 0; i != rows_; ++i)
		grid[i] = new Tile[columns_];
}

void Terrain::fillTerrain()
{
	for(int i = 0; i != rows_; ++i)
		for(int j = 0; j != columns_; ++j)
			grid[i][j] = TileFirst;
}

Terrain::~Terrain()
{
	if (grid != nullptr)
	{
		for(int i = 0; i != rows_; ++i)
			delete[] grid[i];

		delete[] grid;
	}
}


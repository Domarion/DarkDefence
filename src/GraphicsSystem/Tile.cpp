/*
 * Tile.cpp
 *
 *  Created on: 10 марта 2016 г.
 *      Author: kostya_hm
 */

#include "Tile.h"

Tile::Tile(SDL_Texture* ttexture)
:texture(ttexture)
{
	// TODO Auto-generated constructor stub

}

Tile::~Tile()
{
	// TODO Auto-generated destructor stub
	if (texture != nullptr)
		SDL_DestroyTexture(texture);
}

const SDL_Texture& Tile::getTexture() const
{
	return *texture;
}

/*
 * Tile.h
 *
 *  Created on: 10 марта 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include <SDL.h>
#include <SDL_image.h>

class Tile
{
public:
	Tile(SDL_Texture* ttexture = nullptr);
	~Tile();
	const SDL_Texture& getTexture() const;
private:
	SDL_Texture* texture;
};


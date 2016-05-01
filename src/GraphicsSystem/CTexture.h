
#pragma once
#include <SDL2/SDL.h>
#include <string>

class CTexture
{
public:


	CTexture(SDL_Renderer *aRenderer = nullptr, SDL_Texture* aTexture = nullptr, SDL_Rect* aRect = nullptr);
	virtual void draw();

	virtual ~CTexture();

	SDL_Renderer* getRenderer() const;
	void setRenderer(SDL_Renderer* value);
	virtual SDL_Rect* getRect() const;
	virtual void setRect(SDL_Rect* value);
	bool hasRenderer() const;
	void loadTextureFromFile(std::string filename);
	virtual SDL_Texture* getTexture() const;
	void setTextureFromSurface(SDL_Surface* surface);
	void setTexture(SDL_Texture* value);
	SDL_Texture* getTextureFromSurface(SDL_Surface* surface);

protected:
	void CopyTextureToRenderer(SDL_Texture* aTexture, SDL_Rect* sourceRect, SDL_Rect* destRect);
private:
	SDL_Renderer *renderptr;
	SDL_Rect *rect;
	SDL_Texture* texture;

};

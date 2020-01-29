#include "TextureManager.h"

SDL_Texture* TextureManager::loadTexture(const char* file) {

	SDL_Surface* tmp = IMG_Load(file);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmp);
	SDL_FreeSurface(tmp);
	return tex;
}
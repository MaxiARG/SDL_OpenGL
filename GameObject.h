#pragma once
#include "Game.h"

class GameObject
{

public:
	GameObject(const char* textureSheet, int x, int y);
	~GameObject();

	void update();
	void render();

private:
	int x;
	int y;

	SDL_Texture* objectTexture;
	SDL_Rect srcRect, destRect;

};


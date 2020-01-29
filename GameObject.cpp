#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* textureSheet, int x, int y)
{
	objectTexture = TextureManager::loadTexture(textureSheet);
	this->x = x;
	this->y = y;
}

GameObject::~GameObject()
{

}

void GameObject::update()
{
	x++;
	y++;

	srcRect.h = 64;
	srcRect.w = 64;
	srcRect.x = srcRect.y = 0;

	destRect.x = x;
	destRect.y = y;
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;
}

void GameObject::render()
{
	SDL_RenderCopy(Game::renderer, objectTexture, &srcRect, &destRect);
}

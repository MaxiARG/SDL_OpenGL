#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"

GameObject* player;
SDL_Renderer* Game::renderer = nullptr;
Game::Game()
{
	
	isRunning = true;
}

Game::~Game()
{
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "subsistemas inicializados" << std::endl;
		SDL_Window* window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		
		if (window) {
			std::cout << "Window created" << std::endl;
		}

		Game::renderer = SDL_CreateRenderer(window, -1, 0);
		if (Game::renderer) {
			std::cout << "Renderer created" << std::endl;
			SDL_SetRenderDrawColor(Game::renderer, 125, 123, 121, 255);
		}
		isRunning = true;
	}
	else {
		isRunning = false;
	}

	player = new GameObject("character.png", 0, 0);


}

void Game::update()
{
	player->update();
}

void Game::render()
{
	SDL_RenderClear(Game::renderer);

	player->render();

	SDL_RenderPresent(Game::renderer);

}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(Game::renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

bool Game::running()
{
	return isRunning;
}

#include "Game.h"
SDL_Texture* playerPNG;
SDL_Rect srcR, destR;

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

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			std::cout << "Renderer created" << std::endl;
			SDL_SetRenderDrawColor(renderer, 125, 123, 121, 255);
		}
		isRunning = true;
	}
	else {
		isRunning = false;
	}

	SDL_Surface* tmpSurface = IMG_Load("character.png");
	playerPNG = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

}

void Game::update()
{
	destR.h = 64;
	destR.w = 64;

	destR.x += 1;

}

void Game::render()
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, playerPNG, NULL, &destR);

	SDL_RenderPresent(renderer);

}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
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

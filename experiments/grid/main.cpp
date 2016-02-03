#include <iostream>
#include "SDL.h"
#include "Util.h"
#include "Grid.h"
#include "Player.h"

using namespace std;

const int rows = 18;
const int cols = 24;
const int cellSize = 32;

SDL_Window * window;
SDL_Renderer * renderer;
Grid * grid;
Player * player;

void sdlError() {
	cout << SDL_GetError() << endl;
	exit(1);
}

void draw() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	grid->draw();
	player->draw();
	SDL_RenderPresent(renderer);
}

bool processInput() {
	SDL_Event e;
	
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
			return false;
		} else if (e.type == SDL_QUIT) {
			return false;
		} else {
			player->processEvent(&e);
		}
	}
	return true;
}

void init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) sdlError();

	window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, cols * cellSize, rows * cellSize, 0);
	if (window == NULL) sdlError(); 

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) sdlError(); 

	grid = new Grid(renderer, rows, cols, cellSize);
	player = new Player(renderer, grid, 0, 0);
}

void loop() {
	while (processInput()) {
		draw();
		SDL_Delay(50);
	}
}

void shutdown() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main(int argc, char* argv[]) {
	init();
	loop();
	shutdown();
	return 0;
}


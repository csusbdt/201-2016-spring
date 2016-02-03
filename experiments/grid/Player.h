#pragma once

#include "SDL.h"
#include "Grid.h"

class Player {
public:
	Player(SDL_Renderer * renderer, Grid * grid, int x, int y);
	void processEvent(SDL_Event * event);
	void draw() const;

private:
	SDL_Renderer * renderer;
	Grid * grid;
	int x;
	int y;
};


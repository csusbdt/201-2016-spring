/*

This program avoids double buffering -- there is only one drawing surface.

*/

#include <iostream>
#include "SDL.h"
#include "Util.h"

SDL_Window * window;
SDL_Surface * surface;
SDL_Renderer * renderer;

double prob = .03;

void draw() {
	for (int i = 0; i < surface->w; ++i) {
		for (int j = 0; j < surface->h; ++j) {
			if (Util::randomBool(prob)) {
				int hue = Util::randomInt(0, 360);
				double fr, fg, fb;
				Util::HSVtoRGB(&fr, &fg, &fb, hue, 1.0, 1.0);
				char r = Util::doubleToChar(fr);
				char g = Util::doubleToChar(fg);
				char b = Util::doubleToChar(fb);
				SDL_SetRenderDrawColor(renderer, r, g, b, 255);
				SDL_RenderDrawPoint(renderer, i, j);
			}
		}
	}
	SDL_UpdateWindowSurface(window);
}

bool processInput() {
	SDL_Event e;

	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_KEYDOWN) {
		 	if (e.key.keysym.sym == SDLK_ESCAPE) return false;
		} else if (e.type == SDL_QUIT) {
			return false;
		}
	}
	return true;
}

int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) return 1;

	window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 512, 512, 0);
	//window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN);
	surface = SDL_GetWindowSurface(window);
	renderer = SDL_CreateSoftwareRenderer(surface);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	while (processInput()) {
		draw();
		SDL_Delay(50);
	}

	SDL_Quit();
	return 0;
}


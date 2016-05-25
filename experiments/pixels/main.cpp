/*

This program avoids double buffering -- there is only one drawing surface.

*/

#include <iostream>
#include <cassert>
#include "SDL.h"
#include "Util.h"

SDL_Window * window;
SDL_Surface * surface;
SDL_Renderer * renderer;

// x: x position as a percent of window width
// y: y position as a percent of window height
// radius: radius as a percent of window width
// p: density as a probability
void drawDisk(double x, double y, double radius, char r, char g, char b, double p) {
	for (int i = 0; i < surface->w; ++i) {
		for (int j = 0; j < surface->h; ++j) {
			double dist = sqrt((surface->w * x - i) * (surface->w * x - i) + (surface->h * y - j) * (surface->h * y - j));
			double prob = 0;
			double radiusInPixels = radius * surface->w;
			if (dist < radiusInPixels) prob = (radiusInPixels - dist) / radiusInPixels * p;
			if (Util::randomBool(prob)) {
				SDL_SetRenderDrawColor(renderer, r, g, b, 255);
				SDL_RenderDrawPoint(renderer, i, j);
			}
		}
	}
}

void drawPixels(double prob) {
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
	SDL_ShowCursor(SDL_DISABLE);
	SDL_DisplayMode display;
	assert(SDL_GetCurrentDisplayMode(0, &display) == 0);
	window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, display.w, display.h, SDL_WINDOW_FULLSCREEN);
	surface = SDL_GetWindowSurface(window);
	renderer = SDL_CreateSoftwareRenderer(surface);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	drawPixels(1);
	drawDisk(.5, .5, .2, 0, 255, 0, 1.0);
	while (processInput()) {
		drawPixels(.03);
		SDL_UpdateWindowSurface(window);
		SDL_Delay(50);
	}

	SDL_Quit();
	return 0;
}


#include "Player.h"

Player::Player(SDL_Renderer * renderer, Grid * grid, int x, int y) : 
	renderer(renderer), grid(grid), x(x), y(y) {
}

void Player::processEvent(SDL_Event * e) {
	if (e->type == SDL_KEYDOWN) {
		if      (e->key.keysym.sym == SDLK_d) x += 1;
		else if (e->key.keysym.sym == SDLK_a) x -= 1;
		else if (e->key.keysym.sym == SDLK_w) y -= 1;
		else if (e->key.keysym.sym == SDLK_s) y += 1;
	}
}

void Player::draw() const {
	SDL_Rect rect;
	rect.x = grid->getCellSize() * x + grid->getCellSize() / 2 / 2; 
	rect.y = grid->getCellSize() * y + grid->getCellSize() / 2 / 2;
	rect.w = grid->getCellSize() / 2;
	rect.h = grid->getCellSize() / 2;
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &rect);
}


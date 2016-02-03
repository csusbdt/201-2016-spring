#include "SDL.h"
#include "Grid.h"

Grid::Grid(SDL_Renderer * renderer, int rows, int cols, int cellSize) : 
	renderer(renderer), 
	rows(rows), 
	cols(cols),
	cellSize(cellSize) {
}

int Grid::getCellSize() const {
	return cellSize;
}

void Grid::draw() const {
	// Draw horizontal grid lines.
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for (int r = 0; r < rows; ++r) {
		SDL_RenderDrawLine(renderer, 0, r * cellSize, cols * cellSize, r * cellSize);
	}

	// Draw vertical grid lines.
	for (int c = 0; c < cols; ++c) {
		SDL_RenderDrawLine(renderer, c * cellSize, 0, c * cellSize, rows * cellSize);
	}
}


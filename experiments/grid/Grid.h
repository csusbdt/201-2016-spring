#pragma once

class Grid {
public:
	Grid(SDL_Renderer * renderer, int rows, int cols, int cellSize);
	void draw() const;
	int getCellSize() const;

private:
	SDL_Renderer * renderer;
	int rows;
	int cols;
	int cellSize;
};


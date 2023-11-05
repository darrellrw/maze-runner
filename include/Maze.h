#ifndef MAZE_H
#define MAZE_H

#include "Tile.h"

class Maze {
    private:
        int rows = 0;
        int columns = 0;
        int tileSize = 0;

        Tile* grid[MAX_MAZE_HEIGHT_SIZE][MAX_MAZE_WIDTH_SIZE] = {};
        Tile* currentTile = nullptr;

        std::vector<Tile*> stack = {};

    public:
        Maze(int tileSize, int rows, int columns);
        ~Maze();

        void setup();
        void reset();

        Tile* checkNeighbour(Tile* tile);

        void removeWall(Tile *tile1, Tile *tile2);

        void generate(SDL_Renderer* renderer);
};

#endif
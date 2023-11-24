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

        bool mazeComplete = false;
        bool mazeSolved = false;

        int xStart;
        int yStart;

    public:
        Maze(int tileSize, int rows, int columns);
        ~Maze();

        void setup();
        void reset();

        void setStartTile(int x, int y);

        Tile* checkNeighbour(Tile* tile);

        void removeWall(Tile *tile1, Tile *tile2);

        void generate(SDL_Renderer* renderer);

        void mazeRender(SDL_Renderer *renderer);

        bool shortestPath(SDL_Renderer *renderer, int xStart, int yStart, int xEnd, int yEnd);

        void getTile(SDL_Renderer *renderer, int x, int y);
        Tile* getTile(int x, int y);

        void tileInformation(int x, int y);

        bool getMazeStatus();
};

#endif
#include "Header.h"
#include "Maze.h"

Maze::Maze(int tileSize, int rows, int columns) {
    this->tileSize = tileSize;
    this->rows = rows;
    this->columns = columns;
}

Maze::~Maze() {
    // Empty
}

void Maze::setup() {
    // Generating every Tile
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            this->grid[r][c] = new Tile(tileSize, r, c);
        }
    }

    // Set starting Tile
    this->currentTile = this->grid[0][0];

    // Set available neighbour Tile
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            if (r != 0) {
                this->grid[r][c]->setNeighbour(0, this->grid[r - 1][c]);
            }
            else {
                this->grid[r][c]->setNeighbour(0, nullptr);
            }

            if (c != (this->columns - 1)) {
                this->grid[r][c]->setNeighbour(1, this->grid[r][c + 1]);
            }
            else {
                this->grid[r][c]->setNeighbour(1, nullptr);
            }

            if (c != 0) {
                this->grid[r][c]->setNeighbour(2, this->grid[r][c - 1]);
            }
            else {
                this->grid[r][c]->setNeighbour(2, nullptr);
            }

            if (r != (this->rows - 1)) {
                this->grid[r][c]->setNeighbour(3, this->grid[r + 1][c]);
            }
            else {
                this->grid[r][c]->setNeighbour(3, nullptr);
            }
        }
    }
}

void Maze::reset() {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            this->grid[r][c] = nullptr;
        }
    }

    this->currentTile = nullptr;

    this->stack.clear();
}

Tile *Maze::checkNeighbour(Tile* tile) {
    std::vector<Tile*> neighbours;

    if (tile->getNeighbour(0) != nullptr && !tile->getNeighbour(0)->getVisited()) {
        neighbours.push_back(tile->getNeighbour(0));
    }
    if (tile->getNeighbour(1) != nullptr && !tile->getNeighbour(1)->getVisited()) {
        neighbours.push_back(tile->getNeighbour(1));
    }
    if (tile->getNeighbour(2) != nullptr && !tile->getNeighbour(2)->getVisited()) {
        neighbours.push_back(tile->getNeighbour(2));
    }
    if (tile->getNeighbour(3) != nullptr && !tile->getNeighbour(3)->getVisited()) {
        neighbours.push_back(tile->getNeighbour(3));
    }
    
    if (neighbours.size() != 0) {
        return neighbours[(int)(rand() % neighbours.size())];
    }
    else {
        return nullptr;
    }
}

void Maze::removeWall(Tile *tile1, Tile *tile2) {
    int x = (tile1->getLocColumn() - tile2->getLocColumn());
    if (x == 1) {
        tile1->setWall(2, false);
        tile2->setWall(1, false);
    }
    else if (x == -1) {
        tile1->setWall(1, false);
        tile2->setWall(2, false);
    }

    int y = (tile1->getLocRow() - tile2->getLocRow());
    if (y == 1) {
        tile1->setWall(0, false);
        tile2->setWall(3, false);
    }
    else if (y == -1) {
        tile1->setWall(3, false);
        tile2->setWall(0, false);
    }
}

void Maze::generate(SDL_Renderer *renderer) {
    this->currentTile->setVisited(true);

    for (int r = 0; r < this->rows; r++) {
        for (int c = 0; c < this->columns; c++) {
            this->grid[r][c]->showWall(renderer);
        }
    }

    Tile* nextTile = this->checkNeighbour(this->currentTile);

    if (nextTile != nullptr) {
        nextTile->setVisited(true);
        this->stack.push_back(this->currentTile);
        nextTile->drawTile(renderer, 255, 0, 0);
        this->removeWall(this->currentTile, nextTile);
        this->currentTile = nextTile;
    }
    else if (this->stack.size() > 0) {
        Tile* tile = this->stack.back();
        this->stack.pop_back();
        this->currentTile = tile;
        currentTile->drawTile(renderer, 255, 0, 0);
    }
}

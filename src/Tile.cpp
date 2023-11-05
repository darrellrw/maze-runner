#include "Header.h"
#include "Tile.h"

Tile::Tile(int tileSize, int locRow, int locColumn) {
    this->tileSize = tileSize;
    this->locRow = locRow;
    this->locColumn = locColumn;
}

Tile::~Tile() {
    // Empty
}

int Tile::getLocRow() {
    return this->locRow;
}

int Tile::getLocColumn() {
    return this->locColumn;
}

void Tile::setNeighbour(int loc, Tile *value) {
    switch (loc) {
        case 0: {
            this->topNeighbour = value;
        }
        break;
        case 1: {
            this->rightNeighbour = value;
        }
        break;
        case 2: {
            this->leftNeighbour = value;
        }
        break;
        case 3: {
            this->bottomNeighbour = value;
        }
        break;
    }
}

Tile *Tile::getNeighbour(int loc) {
    switch (loc) {
        case 0: {
            return this->topNeighbour;
        }
        break;
        case 1: {
            return this->rightNeighbour;
        }
        break;
        case 2: {
            return this->leftNeighbour;
        }
        break;
        case 3: {
            return this->bottomNeighbour;
        }
        break;

        default:
            return nullptr;
        break;
    }
}

void Tile::setWall(int loc, bool value) {
    switch (loc) {
        case 0: {
            this->topWall = value;
        }
        break;
        case 1: {
            this->rightWall = value;
        }
        break;
        case 2: {
            this->leftWall = value;
        }
        break;
        case 3: {
            this->bottomWall = value;
        }
        break;
    }
}

void Tile::setVisited(bool visit) {
    this->visited = visit;
}

bool Tile::getVisited() {
    return this->visited;
}

void Tile::drawWall(int loc, SDL_Renderer *renderer) {
    switch (loc) {
        case 0: {
            SDL_RenderDrawLine(renderer, (this->locColumn * this->tileSize), (this->locRow * this->tileSize), (this->locColumn * this->tileSize) + this->tileSize, (this->locRow* this->tileSize));
        }
        break;
        case 1: {
            SDL_RenderDrawLine(renderer, (this->locColumn * this->tileSize) + this->tileSize, (this->locRow* this->tileSize), (this->locColumn * this->tileSize) + this->tileSize, (this->locRow * this->tileSize) + this->tileSize);
        }
        break;
        case 2: {
            SDL_RenderDrawLine(renderer, (this->locColumn * this->tileSize), (this->locRow * this->tileSize), (this->locColumn * this->tileSize), (this->locRow * this->tileSize) + this->tileSize);
        }
        break;
        case 3: {
            SDL_RenderDrawLine(renderer, (this->locColumn * this->tileSize), (this->locRow * this->tileSize) + this->tileSize, (this->locColumn * this->tileSize) + this->tileSize, (this->locRow * this->tileSize) + this->tileSize);
        }
        break;
    }
}

void Tile::drawTile(SDL_Renderer *renderer, int r, int g, int b) {
    SDL_Rect rect;
    rect.x = (this->locColumn * this->tileSize) + 1;
    rect.y = (this->locRow * this->tileSize) + 1;
    rect.w = this->tileSize;
    rect.h = this->tileSize;

    SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
}



void Tile::showWall(SDL_Renderer *renderer) {
    if (this->topWall) {
        this->drawWall(0, renderer);
    }
    if (this->rightWall) {
        this->drawWall(1, renderer);
    }
    if (this->leftWall) {
        this->drawWall(2, renderer);
    }
    if (this->bottomWall) {
        this->drawWall(3, renderer);
    }
    if (this->visited) {
        this->drawTile(renderer, 128, 128, 128);
    }
}

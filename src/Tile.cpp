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

std::vector<Tile*> Tile::getVectorNeighbour() {
    std::vector<Tile*> neighbour = {};
    if (this->topNeighbour != nullptr) {
        neighbour.push_back(this->topNeighbour);
    }
    if (this->rightNeighbour != nullptr) {
        neighbour.push_back(this->rightNeighbour);
    }
    if (this->leftNeighbour != nullptr) {
        neighbour.push_back(this->leftNeighbour);
    }
    if (this->bottomNeighbour != nullptr) {
        neighbour.push_back(this->bottomNeighbour);
    }
    return neighbour;
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

void Tile::setHover(bool hover) {
    this->hover = hover;
}

void Tile::setHoverPath(bool hoverPath) {
    this->hoverPath = hoverPath;
}

void Tile::setColp(int loc, bool colp) {
    switch (loc) {
        case 0: {
            this->startingTile = colp;
        }
        break;
        case 1: {
            this->endingTile = colp;
        }
        break;
    }
}

void Tile::drawWall(int loc, SDL_Renderer *renderer) {
    switch (loc) {
        case 0: {
            SDL_RenderDrawLine(renderer, (this->locColumn * this->tileSize), (this->locRow * this->tileSize), (this->locColumn * this->tileSize) + this->tileSize, (this->locRow * this->tileSize));
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
    if (this->hoverPath) {
        this->drawTile(renderer, 34, 0, 255);
    }
    if (this->startingTile) {
        this->drawTile(renderer, 255, 255, 0);
    }
    if (this->endingTile) {
        this->drawTile(renderer, 128, 255, 0);
    }
    if (this->hover) {
        this->drawTile(renderer, 128, 0, 0);
    }
}

void Tile::tileInformation() {
    std::cout << "Location: " << this->locRow << " " << this->locColumn << std::endl;
    if (this->topNeighbour != nullptr) {
        std::cout << "Neigbor Top: " << this->topNeighbour->getLocRow() << " " << this->topNeighbour->getLocColumn() << std::endl;
    }
    else {
         std::cout << "Neigbor Top: NULL" << std::endl;
    }

    if (this->rightNeighbour != nullptr) {
        std::cout << "Neigbor Rigth: " << this->rightNeighbour->getLocRow() << " " << this->rightNeighbour->getLocColumn() << std::endl;
    }
    else {
         std::cout << "Neigbor Right: NULL" << std::endl;
    }

    if (this->leftNeighbour != nullptr) {
        std::cout << "Neigbor Left: " << this->leftNeighbour->getLocRow() << " " << this->leftNeighbour->getLocColumn() << std::endl;
    }
    else {
         std::cout << "Neigbor Left: NULL" << std::endl;
    }

    if (this->bottomNeighbour != nullptr) {
        std::cout << "Neigbor Bottom: " << this->bottomNeighbour->getLocRow() << " " << this->bottomNeighbour->getLocColumn() << std::endl;
    }
    else {
         std::cout << "Neigbor Bottom: NULL" << std::endl;
    }

}

void Tile::neighbourNull() {
    if (this->topWall) {
        this->topNeighbour = nullptr;
    }
    if (this->rightWall) {
        this->rightNeighbour = nullptr;
    }
    if (this->leftWall) {
        this->leftNeighbour = nullptr;
    }
    if (this->bottomWall) {
        this->bottomNeighbour = nullptr;
    }
}
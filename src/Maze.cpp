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
    this->mazeComplete = false;
    this->mazeSolved = false;

    this->stack.clear();
}

void Maze::setStartTile(int x, int y) {
    // Set starting Tile
    this->xStart = x;
    this->yStart = y;
    this->currentTile = this->grid[this->yStart][this->xStart];
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
    
    if (neighbours.size() != 0) { // Randomisasi penentuan rute DFS
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

void Maze::mazeRender(SDL_Renderer *renderer) {
    for (int r = 0; r < this->rows; r++) {
        for (int c = 0; c < this->columns; c++) {
            this->grid[r][c]->showWall(renderer);
        }
    }
}

void Maze::generate(SDL_Renderer *renderer) {
    if (!this->mazeComplete) {
        this->currentTile->setVisited(true);

        Tile* nextTile = this->checkNeighbour(this->currentTile);
        Tile* tile = nullptr;

        if (nextTile != nullptr) { // Check Neighbour for Generating
            nextTile->setVisited(true);
            this->stack.push_back(this->currentTile);
            nextTile->drawTile(renderer, 255, 0, 0);
            this->removeWall(this->currentTile, nextTile);
            this->currentTile = nextTile;
        }
        else if (this->stack.size() > 0) { // Backtracking
            tile = this->stack.back();
            this->stack.pop_back();
            this->currentTile = tile;
            currentTile->drawTile(renderer, 255, 0, 0);
        }

        if (tile == this->grid[this->yStart][this->xStart]) {  // Jika sudah tidak ada lagi tile yang dapat dikunjungi (Stack kosong)
            this->mazeComplete = true;
            std::cout << "MAZE COMPLETE" << std::endl;
            for (int r = 0; r < rows; r++) {
                for (int c = 0; c < columns; c++) {
                    this->grid[r][c]->setVisited(false);
                    this->grid[r][c]->neighbourNull();
                }
            }
        }
    }
}

bool Maze::shortestPath(SDL_Renderer *renderer, int xStart, int yStart, int xEnd, int yEnd) { // BFS karena modifikasi DFS untuk unweight membingungkan
    if (this->mazeComplete && !this->mazeSolved) {
        std::list<Tile*> queue = {};

        std::map<Tile*, Tile*> pred = {};

        this->grid[xStart][yStart]->setColp(0, true);

        Tile* startTile = this->grid[xStart][yStart]; // Masukkan Input
        startTile->setVisited(true);

        queue.push_back(startTile);
        pred[startTile] = nullptr;

        while (!queue.empty()) {
            Tile* u = queue.front(); // Inisiasi U
            queue.pop_front();

            for (int i = 0; i < u->getVectorNeighbour().size(); i++) {
                if (!u->getVectorNeighbour()[i]->getVisited()) {
                    u->getVectorNeighbour()[i]->setVisited(true);
                    queue.push_back(u->getVectorNeighbour()[i]); // Masukkan Neigbour ke Queue
                    pred[u->getVectorNeighbour()[i]] = u; // Masukkan sebagai path prediction

                    if (u->getVectorNeighbour()[i] == this->grid[xEnd][yEnd]) { // Neighbour End Tile?
                        this->grid[xEnd][yEnd]->setColp(1, true);

                        std::vector<Tile*> path;
                        Tile* crawl = this->grid[xEnd][yEnd];

                        path.push_back(crawl);

                        while (crawl != nullptr) {  // Melakukan perjalanan mundur dari pred
                            path.push_back(crawl);
                            crawl = pred[crawl];
                        }              

                        for (int hh = path.size() - 1; hh >= 0; hh--) {
                            path[hh]->setHoverPath(true);
                        }

                        for (int r = 0; r < rows; r++) {
                            for (int c = 0; c < columns; c++) {
                                this->grid[r][c]->setVisited(false);
                            }
                        }
                        std::cout << "SOLVED" << std::endl;
                        this->mazeSolved = true;
                        return true;
                    }
                }
            }
        }
    }
    this->mazeSolved = false;
    return false;
}

void Maze::getTile(SDL_Renderer *renderer, int x, int y) {
     for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            if (this->grid[r][c] == this->grid[y][x]) {
                this->grid[y][x]->setHover(true);
            }
            else {
                this->grid[r][c]->setHover(false);
            }
        }
    }
}

Tile* Maze::getTile(int x, int y) {
    return this->grid[y][x];
}

void Maze::tileInformation(int x, int y) {
    this->grid[y][x]->tileInformation();
}

bool Maze::getMazeStatus() {
    return this->mazeComplete;
}
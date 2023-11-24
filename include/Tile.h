#ifndef TILE_H
#define TILE_H

class Tile {
    private:
        int tileSize = 0;
        int locRow = 0;
        int locColumn = 0;

        bool topWall = true;
        bool rightWall = true;
        bool leftWall = true;
        bool bottomWall = true;

        bool visited = false;
        bool hover = false;
        bool hoverPath = false;

        bool startingTile = false;
        bool endingTile = false;

        Tile* topNeighbour = nullptr;
        Tile* rightNeighbour = nullptr;
        Tile* leftNeighbour = nullptr;
        Tile* bottomNeighbour = nullptr;

    public:
        Tile(int tileSize, int locRow, int locColumn);
        ~Tile();

        int getLocRow();
        int getLocColumn();

        void setNeighbour(int loc, Tile* value);
        Tile* getNeighbour(int loc);
        std::vector<Tile*> getVectorNeighbour();

        void setWall(int loc, bool value);

        void setVisited(bool visit);
        bool getVisited();

        void setHover(bool hover);
        void setHoverPath(bool hoverPath);
        void setColp(int loc, bool colp);

        void drawWall(int loc, SDL_Renderer* renderer);
        void drawTile(SDL_Renderer* renderer, int r, int g, int b);

        void showWall(SDL_Renderer* renderer);

        void tileInformation();

        void neighbourNull();
};

#endif
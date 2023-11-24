#include "Header.h"
#include "Maze.h"

int main(int argc, char** argv) {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
        return -1;
    }

    std::cout << "WINDOW OPEN" << std::endl;

    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,  SCREEN_HEIGHT, 0);

    if (!window) {
        std::cout << "SDL Failed to Create Window" << std::endl;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool game = true;

    int xMouse;
    int yMouse;

    bool startSelected = false;

    Maze* maze = new Maze(16, 32, 32);
    maze->setup();

    std::cout << "SELECT STARTING TILE FOR GENERATE MAZE" << std::endl;

    while (game) {
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                game = false;
            }
            if (event.type == SDL_KEYDOWN) { // Reset Button
                if (event.key.keysym.sym == SDLK_r) {
                    std::cout << "MAZE RESET" << std::endl;
                    startSelected = false;
                    maze->reset();
                    maze->setup();
                }

                if (event.key.keysym.sym == SDLK_q) { // Debug Button
                    if (!maze->getMazeStatus()) {
                        std::cout << "PLEASE WAIT FOR THE MAZE TO BE GENERATED" << std::endl;
                    }
                    else {
                        maze->shortestPath(renderer, 31, 14, 5, 5);
                    }
                }
            }

            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    if (!startSelected) {
                        startSelected = true;
                        maze->setStartTile(int(xMouse / 16), int(yMouse / 16));
                    }
                }
                if (event.button.button == SDL_BUTTON_RIGHT) {
                    if (!maze->getMazeStatus()) {
                        std::cout << "PLEASE WAIT FOR THE MAZE TO BE GENERATED" << std::endl;
                    }
                    else {
                        maze->tileInformation(int(xMouse / 16), int(yMouse / 16));
                    }
                }
            }
            else if (event.type == SDL_MOUSEMOTION) {
                SDL_GetMouseState(&xMouse, &yMouse);
                maze->getTile(renderer, int(xMouse / 16), int(yMouse / 16));
            }
        }
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

        maze->mazeRender(renderer);

        if (startSelected) {
            maze->generate(renderer);
        }
        
        SDL_RenderPresent(renderer);
    }

    std::cout << "WINDOW CLOSED" << std::endl;

    return 0;
}

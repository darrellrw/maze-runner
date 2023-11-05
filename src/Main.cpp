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

    Maze* maze = new Maze(16, 32, 32);
    maze->setup();

    while (game) {
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                game = false;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_r) {
                    maze->reset();
                    maze->setup();
                }
            }
        }
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

        maze->generate(renderer);
        
        SDL_RenderPresent(renderer);
    }

    std::cout << "WINDOW CLOSED" << std::endl;

    return 0;
}

#include <SDL.h>

int main(int argc, char* args []) {
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("SpaceHunter - C++ Project", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }


    SDL_SetRenderDrawColor(renderer, 100, 100, 180, 255); // Set the background color to purple
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Set the background color to purple
    SDL_Rect rect = {100, 100, 200, 150}; // x, y, width, height

    // Draw the rectangle
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);

    bool running = true;
    SDL_Event event;
    int i = 0;
    while (running) {
        // Close window with any input
        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP){
                i++;

                SDL_SetRenderDrawColor(renderer, 100, 100, 180, 255); // Set the background color to purple
                SDL_RenderClear(renderer);
                SDL_RenderPresent(renderer);

                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Set the background color to purple
                SDL_Rect rect = {100+i, 100, 200, 150}; // x, y, width, height

                // Draw the rectangle
                SDL_RenderFillRect(renderer, &rect);
                SDL_RenderPresent(renderer);
            }

            // Press Escape to Quit
            if ((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)|| event.type == SDL_QUIT) {
                running = false;
                break;
            }
        }




    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

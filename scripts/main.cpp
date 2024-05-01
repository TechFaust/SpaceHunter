#include <SDL.h>
#include "SDL_image.h"
#include "Player/Player.hpp"
#include "Background/Background.hpp"
#include <iostream>

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

    Background background(renderer,"../resources/background_space_1.png");

    Player player(100,10,10,renderer,"PlayerSpaceship");

    bool running = true;
    SDL_Event event;
    int frame_count = 0;

    while (running) {
        // Close window with any input
        while (SDL_PollEvent(&event)) {

            player.Action(event);

            // Press Escape to Quit
            if ((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)|| event.type == SDL_QUIT) {
                running = false;
                break;
            }
        }

        frame_count++;
        if(frame_count > 1000){
            player.Animate();
            frame_count = 0;
        }


        SDL_RenderClear(renderer);
        background.RedrawBackground(renderer);
        player.Render(renderer);
        SDL_RenderPresent(renderer);


    }

    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

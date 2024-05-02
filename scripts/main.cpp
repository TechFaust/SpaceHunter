#include <SDL.h>
#include "SDL_image.h"
#include "Player/Player.hpp"
#include "Background/Background.hpp"
#include "Utilities/SDL_Wrapper.hpp"
#include <iostream>
#include <memory>
using std::make_unique;

int main(int argc, char* args []) {
    SDL_Init(SDL_INIT_EVERYTHING);

    auto Wrapper = make_unique<SDL_Wrapper>(800, 600, "SpaceHunter - C++ Project");

    Background background(Wrapper->getRenderer(),"../resources/background_space_1.png");

    Player player(100,10,10,Wrapper->getRenderer(),"PlayerSpaceship");

    bool running = true;
    SDL_Event event;
    int frame_count = 0;

    while (running) {
        // Close window with any input
        while (SDL_PollEvent(&event)) {

            player.Action(event,Wrapper->getRenderer());

            // Press Escape to Quit
            if ((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)|| event.type == SDL_QUIT) {
                running = false;
                break;
            }
        }


        // Remove bullets that are out of the screen
        for (auto it = player.GetBullets().begin(); it != player.GetBullets().end(); /* no increment here */) {
            if (it->GetPosition().y < 0) { // assuming 0 is the top of the screen
                it = player.GetBullets().erase(it);
            } else {
                ++it;
            }
        }


        frame_count++;
        if(frame_count > 1000){
            player.Animate();
            for(auto &bullet : player.GetBullets()){
                bullet.Move();
                bullet.Animate();
            }
            frame_count = 0;
        }


        SDL_RenderClear(Wrapper->getRenderer());
        background.RedrawBackground(Wrapper->getRenderer());
        player.Render(Wrapper->getRenderer());
        for(auto &bullet : player.GetBullets()){
            bullet.Render(Wrapper->getRenderer());
        }
        SDL_RenderPresent(Wrapper->getRenderer());


    }


    SDL_Quit();
    return 0;
}

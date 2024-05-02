#include <SDL.h>
#include "SDL_image.h"
#include "Player/Player.hpp"
#include "Background/Background.hpp"
#include "Utilities/SDL_Wrapper.hpp"
#include "Enemy/Enemy.hpp"
#include <iostream>
#include <memory>
using std::make_unique;

bool checkCollision(SDL_Rect a, SDL_Rect b);

int main(int argc, char* args []) {
    SDL_Init(SDL_INIT_EVERYTHING);

    auto Wrapper = make_unique<SDL_Wrapper>(800, 600, "SpaceHunter - C++ Project");

    Background background(Wrapper->getRenderer(),"../resources/background_space_1.png");

    Player player(100,10,10,Wrapper->getRenderer(),"PlayerSpaceship");

    std::vector<Enemy> enemies;

    bool running = true;
    SDL_Event event;
    int frame_count = 0;
    int spawn_frame = 0;

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

        for (auto it = enemies.begin(); it != enemies.end(); /* no increment here */) {
            if (it->GetPosition().y > 600) { // assuming 600 is the bottom of the screen
                it = enemies.erase(it);
            } else {
                ++it;
            }
        }

        for (auto bullet_it = player.GetBullets().begin(); bullet_it != player.GetBullets().end(); /* no increment here */) {
            for (auto enemy_it = enemies.begin(); enemy_it != enemies.end(); /* no increment here */) {
                if (checkCollision(bullet_it->GetPosition(), enemy_it->GetPosition())) {

                    enemy_it->IsAttacked(bullet_it->GetDamage());
                    if(enemy_it->GetState() == DEAD){
                        enemy_it = enemies.erase(enemy_it);
                    }

                    bullet_it = player.GetBullets().erase(bullet_it);

                    break;
                } else {
                    ++enemy_it;
                }
            }
            if (bullet_it != player.GetBullets().end()) {
                ++bullet_it;
            }
        }


        frame_count++;
        spawn_frame++;
        if(spawn_frame > 3000){
            enemies.emplace_back(10,10,0,Wrapper->getRenderer(),"Meteor");
            spawn_frame = 0;
        }

        if(frame_count > 1000){
            player.Animate();
            for(auto &bullet : player.GetBullets()){
                bullet.Move();
                bullet.Animate();
            }
            for(auto &enemy : enemies){
                enemy.Move_Enemy();
                enemy.Animate();
            }
            frame_count = 0;
        }


        SDL_RenderClear(Wrapper->getRenderer());
        background.RedrawBackground(Wrapper->getRenderer());
        player.Render(Wrapper->getRenderer());
        for(auto &bullet : player.GetBullets()){
            bullet.Render(Wrapper->getRenderer());
        }
        for(auto &enemy : enemies){
            enemy.Render(Wrapper->getRenderer());
        }
        SDL_RenderPresent(Wrapper->getRenderer());


    }


    SDL_Quit();
    return 0;
}

bool checkCollision(SDL_Rect a, SDL_Rect b) {
    // The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    // Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    // Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    // If any of the sides from A are outside of B
    if (bottomA <= topB) {
        return false;
    }

    if (topA >= bottomB) {
        return false;
    }

    if (rightA <= leftB) {
        return false;
    }

    if (leftA >= rightB) {
        return false;
    }

    // If none of the sides from A are outside B
    return true;
}
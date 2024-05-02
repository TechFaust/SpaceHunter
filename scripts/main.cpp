#include <SDL.h>
#include "SDL_image.h"
#include "Player/Player.hpp"
#include "Background/Background.hpp"
#include "Utilities/SDL_Wrapper.hpp"
#include "Enemy/Enemy.hpp"
#include "Menu/Menu.hpp"
#include <iostream>
#include <memory>
#include "SDL_ttf.h"
#include "Enemy/DoomShip.hpp"
#include "Enemy/Ship.hpp"
#include <vector>
// #include <SDL_mixer.h>
using std::make_unique;

bool checkCollision(SDL_Rect a, SDL_Rect b);

int main(int argc, char* args []) {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("../resources/font/eras-bold-bt.ttf", 24);

    auto Wrapper = make_unique<SDL_Wrapper>(800, 600, "SpaceHunter - C++ Project");

    Background background(Wrapper->getRenderer(),"../resources/background_space_1.png");

    Player player(100,10,10,10,Wrapper->getRenderer(),"PlayerSpaceship");

    Menu menu(Wrapper->getRenderer(), false, false);

    std::vector<std::unique_ptr<Enemy>> enemies;

    bool running = true;
    SDL_Event event;
    int frame_count = 0;
    int spawn_frame = 0;

    while (running) {

        while (SDL_PollEvent(&event)) {

            if (menu.GetGameStarted()) {
                player.Action(event,Wrapper->getRenderer());
            } else {
                menu.handleEvent(event);
            }
            // Press Escape to Quit
            if (((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)|| event.type == SDL_QUIT)||menu.GetQuitGame()) {
                running = false;
                break;
            }
        }

        SDL_RenderClear(Wrapper->getRenderer());

        if(menu.GetGameStarted()) {
            // Remove bullets that are out of the screen
            for (auto it = player.GetBullets().begin(); it != player.GetBullets().end(); /* no increment here */) {
                if (it->GetPosition().y < 0) { // assuming 0 is the top of the screen
                    it = player.GetBullets().erase(it);
                } else {
                    ++it;
                }
            }



            for (auto it = enemies.begin(); it != enemies.end(); /* no increment here */) {
                if ((*it)->GetPosition().y >= 580) { // assuming 600 is the bottom of the screen
                    it = enemies.erase(it);
                } else {
                    ++it;
                }
            }

            // Inside your main game loop
            for (auto& enemy : enemies) {
                for (auto it = (*enemy).GetBullets_Enemy().begin(); it != (*enemy).GetBullets_Enemy().end(); /* no increment here */) {
                    if (it->GetPosition().y > 600) { // assuming 600 is the bottom of the screen
                        it = (*enemy).GetBullets_Enemy().erase(it);
                    } else if (checkCollision(player.GetPosition(), it->GetPosition())) {
                        player.IsAttacked(it->GetDamage());
                        it = (*enemy).GetBullets_Enemy().erase(it);
                    } else {
                        ++it;
                    }
                }
            }



            for (auto bullet_it = player.GetBullets().begin();
                 bullet_it != player.GetBullets().end(); /* no increment here */) {
                for (auto enemy_it = enemies.begin(); enemy_it != enemies.end(); /* no increment here */) {
                    if (checkCollision(bullet_it->GetPosition(), (*enemy_it)->GetPosition())) {

                        (*enemy_it)->IsAttacked(bullet_it->GetDamage());
                        if ((*enemy_it)->GetState() == DEAD) {
                            enemy_it = enemies.erase(enemy_it);
                            player.Add_Score(5);
                        }

                        bullet_it = player.GetBullets().erase(bullet_it);
                        player.Add_Score(2);

                        break;
                    } else {
                        ++enemy_it;
                    }
                }
                if (bullet_it != player.GetBullets().end()) {
                    ++bullet_it;
                }
            }

            for (auto enemy_it = enemies.begin(); enemy_it != enemies.end(); /* no increment here */) {
                if (checkCollision(player.GetPosition(), (*enemy_it)->GetPosition())) {
                    player.IsAttacked((*enemy_it)->GetDamage());
                    enemy_it = enemies.erase(enemy_it);
                    player.Add_Score(1);
                } else {
                    ++enemy_it;
                }
            }




            frame_count++;
            spawn_frame++;
            if (spawn_frame > 3000) {
                if(enemies.size() < 10) {
                    switch (rand() % 3) {
                        case 0:
                            enemies.emplace_back(std::make_unique<Enemy>(10, 10, 0, 20, Wrapper->getRenderer(), "Meteor"));
                            break;
                        case 1:
                            enemies.emplace_back(std::make_unique<Ship>(10, 10, 0, 20, Wrapper->getRenderer(), "EnemyShip"));
                            break;
                        case 2:
                            enemies.emplace_back(std::make_unique<DoomShip>(20, 10, 0, 20, Wrapper->getRenderer(), "EnemyDoomShip"));
                            break;
                    }
                }
                }


            if (frame_count > 1000) {
                player.Animate();
                player.ReduceDelay(2);
                for (auto &bullet: player.GetBullets()) {
                    bullet.Move();
                    bullet.Animate();
                }
                for (auto &enemy: enemies) {
                    enemy->Move_Enemy();
                    enemy->ReduceDelay(1);
                    enemy->Shoot_Enemy(Wrapper->getRenderer());

                    for (auto& bullet : enemy->GetBullets_Enemy()) {
                        bullet.Move();
                        bullet.Animate();
                    }
                    enemy->Animate();
                }

                frame_count = 0;
            }

            background.RedrawBackground(Wrapper->getRenderer());
            player.Render(Wrapper->getRenderer());

            for (auto &bullet: player.GetBullets()) {
                bullet.Render(Wrapper->getRenderer());
            }
            for (auto &enemy: enemies) {
                enemy->Render(Wrapper->getRenderer());
                for (auto& bullet : enemy->GetBullets_Enemy()) {
                    bullet.Render(Wrapper->getRenderer());
                }
            }
            player.RenderHealthBar(Wrapper->getRenderer());
            player.RenderScore(Wrapper->getRenderer(), font);
        }
        else {
            background.RedrawBackground(Wrapper->getRenderer());
            menu.render(Wrapper->getRenderer());
        }
        if(player.GetState() == DEAD){
            menu.SetGameStarted(false);
            menu.SetQuitGame(false);
            player.SetState(ALIVE);
            player.SetHealth(100);
            player.SetScore(0);
            enemies.clear();
        }
        SDL_RenderPresent(Wrapper->getRenderer());


    }

    TTF_Quit();
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
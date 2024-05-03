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
#include "Enemy/Meteor.hpp"
#include "Utilities/GameManager.hpp"
#include <vector>
#include <SDL_mixer.h>

using std::make_unique;

bool checkCollision(SDL_Rect a, SDL_Rect b);

int main(int argc, char* args []) {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("../resources/font/eras-bold-bt.ttf", 24);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Music* backgroundMusic = Mix_LoadMUS("../resources/music/MenuTheme.ogg");
    Mix_Music* gameMusic = Mix_LoadMUS("../resources/music/LevelTheme.ogg");

    GameManager gameManager;

    auto Wrapper = make_unique<SDL_Wrapper>(800, 600, "SpaceHunter - C++ Project");

    Background background(Wrapper->getRenderer(),"../resources/background_space_1.png");

    Player player(100,10,10,5,Wrapper->getRenderer(),"PlayerSpaceship");

    Menu menu(Wrapper->getRenderer(), false, false);

    std::vector<std::unique_ptr<Enemy>> enemies;

    Mix_VolumeMusic(MIX_MAX_VOLUME / 10);

    bool running = true;
    SDL_Event event;
    int frame_count = 0;
    int spawn_frame = 0;
    bool background_music_on = true;
    bool game_music_on = false;

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

            if(game_music_on){
                Mix_PlayMusic(gameMusic, -1);
                game_music_on = false;
                background_music_on = true;
            }


            gameManager.checkBulletEnemyCollision(player, enemies);
            gameManager.checkPlayerEnemyCollision(player, enemies);
            gameManager.removeBulletsOutOfScreen(player);
            gameManager.removeEnemiesOutOfScreen(enemies);
            gameManager.checkEnemyBulletPlayerCollision(player, enemies);




            frame_count++;
            spawn_frame++;
            if (spawn_frame > 3000) {
                if(enemies.size() < 10) {
                    switch (rand() % 4) {
                        case 0:
                            enemies.emplace_back(std::make_unique<Meteor>(10, 10, 0, Wrapper->getRenderer(), "Meteor"));
                            break;
                        case 1:
                            enemies.emplace_back(std::make_unique<Ship>(10, 10, 20, Wrapper->getRenderer(), "EnemyShip"));
                            break;
                        case 2:
                            enemies.emplace_back(std::make_unique<DoomShip>(20, 10, 35, Wrapper->getRenderer(), "EnemyDoomShip"));
                            break;
                    }
                    spawn_frame = 0;
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

            player.Upgrade();

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

            if(background_music_on){
                Mix_PlayMusic(backgroundMusic, -1);
                background_music_on = false;
                game_music_on = true;
            }

            background.RedrawBackground(Wrapper->getRenderer());
            menu.render(Wrapper->getRenderer());

        }
        if(player.GetState() == DEAD){
            menu.SetGameStarted(false);
            menu.SetQuitGame(false);
            player.SetState(ALIVE);
            player.SetHealth(100);
            player.SetScore(0);
            player.SetUpgrade(false);
            enemies.clear();
        }
        SDL_RenderPresent(Wrapper->getRenderer());


    }

    TTF_Quit();
    SDL_Quit();
    return 0;
}
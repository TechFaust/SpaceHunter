#include <SDL.h> // Librairie SDL
#include "SDL_ttf.h" // Librairie SDL_TTF (pour la gestion des polices)
#include <SDL_mixer.h> // Librairie SDL_Mixer (pour la gestion du son)

#include <iostream>
#include <memory>
#include <vector>

#include "Utilities/GameManager.hpp" // Classe GameManager
#include "Background/Background.hpp" // Classe Background
#include "Menu/Menu.hpp" // Classe Menu
#include "Utilities/SDL_Wrapper.hpp" // Classe SDL_Wrapper

#include "Player/Player.hpp" // Classe Player
#include "Enemy/Enemy.hpp" // Classe Enemy

#include "Enemy/DoomShip.hpp" // Classe DoomShip
#include "Enemy/Ship.hpp" // Classe Ship
#include "Enemy/Meteor.hpp" // Classe Meteor


using std::make_unique; // Utilisation de la fonction make_unique pour le pointeur unique

int main(int argc, char* args []) {

    // Initialisation de la SDL, de la SDL_TTF et de la SDL_Mixer
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("../resources/font/eras-bold-bt.ttf", 24);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Music* backgroundMusic = Mix_LoadMUS("../resources/music/MenuTheme.ogg");
    Mix_Music* gameMusic = Mix_LoadMUS("../resources/music/LevelTheme.ogg");

    GameManager gameManager; // Init du gameManager

    auto Wrapper = make_unique<SDL_Wrapper>(800, 600, "SpaceHunter - C++ Project"); // Init de la fenêtre

    Background background(Wrapper->getRenderer(),"../resources/background_space_1.png"); // Init du background

    Player player(100,10,10,5,Wrapper->getRenderer(),"PlayerSpaceship"); // Init du joueur

    Menu menu(Wrapper->getRenderer(), false, false); // Init du menu

    std::vector<std::unique_ptr<Enemy>> enemies; // Init du vecteur d'ennemis

    Mix_VolumeMusic(MIX_MAX_VOLUME / 10); // Réglage du volume de la musique (10%, le son est très fort par défaut

    bool running = true; // Booléen pour la boucle principale
    SDL_Event event; // Event de la SDL, pour la gestion des événements

    int frame_count = 0; // Compteur de frames
    int spawn_frame = 0; // Compteur de frames pour le spawn des ennemis

    bool background_music_on = true; // Booléen pour la musique de fond du menu
    bool game_music_on = false; // Booléen pour la musique de jeu

    while (running) {

        while (SDL_PollEvent(&event)) {
            // Gestion des évènements en fonction du menu ou du jeu
            if (menu.GetGameStarted()) {
                player.Action(event,Wrapper->getRenderer());
            } else {
                menu.handleEvent(event);
            }
            // Si on appuye sur la touche Echap ou si on clique sur la croix de la fenêtre, on quitte le jeu
            if (((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)|| event.type == SDL_QUIT)||menu.GetQuitGame()) {
                running = false;
                break;
            }
        }

        SDL_RenderClear(Wrapper->getRenderer()); // Clear de la fenêtre

        if(menu.GetGameStarted()) {

            // Si on est dans le jeu, on lance la musique de jeu si elle n'est pas lancée, en boucle
            if(game_music_on){
                Mix_PlayMusic(gameMusic, -1);
                game_music_on = false;
                background_music_on = true;
            }


            // Gestion des collisions, des déplacements, des tirs, des animations, des upgrades, des scores, etc.
            gameManager.checkBulletEnemyCollision(player, enemies);
            gameManager.checkPlayerEnemyCollision(player, enemies);
            gameManager.removeBulletsOutOfScreen(player);
            gameManager.removeEnemiesOutOfScreen(enemies);
            gameManager.checkEnemyBulletPlayerCollision(player, enemies);




            frame_count++; // Incrémentation du compteur de frames
            spawn_frame++; // Incrémentation du compteur de frames pour le spawn des ennemis

            // Spawn des ennemis toutes les 3000 frames
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


            // Animation, déplacement, tirs, etc. des ennemis et du joueur toutes les 1000 frames
            if (frame_count > 1000) {
                player.Animate();
                player.ReduceDelay(2);
                // Iteration pour chaque missiles du joueur
                for (auto &bullet: player.GetBullets()) {
                    bullet.Move();
                    bullet.Animate();
                }
                // Iteration pour chaque ennemi, ainsi que pour chaque missile de chaque ennemi
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

            player.Upgrade(); // Détection de l'upgrade du joueur par rapport à son score (Unlock le double tirs)

            background.RedrawBackground(Wrapper->getRenderer()); // On redessine le background en premier
            player.Render(Wrapper->getRenderer()); // puis le joueur

            // Puis chaque balle du joueur
            for (auto &bullet: player.GetBullets()) {
                bullet.Render(Wrapper->getRenderer());
            }
            // Puis chaque ennemis, ainsi que chaque balle de chaque ennemi
            for (auto &enemy: enemies) {
                enemy->Render(Wrapper->getRenderer());
                for (auto& bullet : enemy->GetBullets_Enemy()) {
                    bullet.Render(Wrapper->getRenderer());
                }
            }
            player.RenderHealthBar(Wrapper->getRenderer()); // On redessine la barre de vie du joueur
            player.RenderScore(Wrapper->getRenderer(), font); // Ainsi que son score
        }
        else {

            // Dans le cas où on est encore sur le menu, on lance la musique de fond du menu si elle n'est pas lancée,
            // en boucle
            if(background_music_on){
                Mix_PlayMusic(backgroundMusic, -1);
                background_music_on = false;
                game_music_on = true;
            }

            background.RedrawBackground(Wrapper->getRenderer()); // On redessine le background
            menu.render(Wrapper->getRenderer()); // Et le menu

        }
        // Si le joueur est mort, on réinitialise le jeu et on retourne au menu.
        // WORK IN PROGRESS : On pourrait ajouter un écran de fin de partie, avec le score, le nombre d'ennemis tués, etc.
        if(player.GetState() == DEAD){
            menu.SetGameStarted(false);
            menu.SetQuitGame(false);
            player.SetState(ALIVE);
            player.SetHealth(100);
            player.SetScore(0);
            player.SetUpgrade(false);
            player.SetPosition(350,500);
            enemies.clear();
        }
        SDL_RenderPresent(Wrapper->getRenderer()); // On render tout ce qu'on a redessiner,
        // dans l'ordre d'appel d'appels des fonctions RenderCopy


    }

    TTF_Quit(); // On quitte le TTF
    SDL_Quit(); // On quitte la SDL
    return 0;
}
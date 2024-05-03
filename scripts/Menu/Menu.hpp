//
// Created by Groupe_2_Space_Hunter on 02/05/2024.
//

#ifndef SPACEHUNTER_MENU_HPP
#define SPACEHUNTER_MENU_HPP

#include <SDL.h>
#include <SDL_image.h>

/**
 * @brief Menu du jeu, affiche le jeu et s'occupe de la gestion des événements concernant le menu
 */
class Menu {
private:
    SDL_Texture* title; // Titre du jeu
    SDL_Texture* startButton; // Bouton de démarrage
    SDL_Texture* quitButton; // Bouton de quitter

    bool gameStarted; // Check si le jeu a démarré
    bool quitGame; // Check si le jeu doit quitter

public:
    Menu(SDL_Renderer* renderer, bool _gameStarted, bool _quitGame);
    void handleEvent(SDL_Event& e);
    void render(SDL_Renderer* renderer);

    [[nodiscard]] bool GetGameStarted() const;
    [[nodiscard]] bool GetQuitGame() const;

    void SetGameStarted(bool _gameStarted);
    void SetQuitGame(bool _quitGame);
};


#endif //SPACEHUNTER_MENU_HPP

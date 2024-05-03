//
// Created by Groupe_2_Space_Hunter on 02/05/2024.
//

#include "Menu.hpp"

/**
 * @brief Constructeur du menu
 * @param renderer Moteur Graphique
 * @param _gameStarted Booléen pour savoir si le jeu a démarré
 * @param _quitGame Boléen pour savoir si le jeu doit quitter
 */
Menu::Menu(SDL_Renderer* renderer, bool _gameStarted, bool _quitGame) : gameStarted(_gameStarted), quitGame(_quitGame){
    // Load the images for the title, start button, and quit button
    title = IMG_LoadTexture(renderer, "../resources/title.png");
    startButton = IMG_LoadTexture(renderer, "../resources/start_button.png");
    quitButton = IMG_LoadTexture(renderer, "../resources/quit_button.png");
}

/**
 * @brief Gestion des événements du menu (gestion des clics)
 * @param e Evenement
 */
void Menu::handleEvent(SDL_Event& e) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        // Check if the start button was clicked
        // You'll need to replace these coordinates with the actual position and size of your start button
        if (x > 100 && x < 700 && y > 250 && y < 350) {
            gameStarted = true;
        }

        // Check if the quit button was clicked
        // You'll need to replace these coordinates with the actual position and size of your quit button
        if (x > 100 && x < 700 && y > 450 && y < 550) {
            // Quit the game
            quitGame = true;
        }
    }
}

/**
 * @brief Affichage du menu (boutons & titre)
 * @param renderer Moteur Graphique
 */
void Menu::render(SDL_Renderer* renderer) {
    // Render the title, start button, and quit button
    // You'll need to replace these SDL_Rects with the actual position and size of your title, start button, and quit button
    SDL_Rect titleRect = {100, 100, 600, 100};
    SDL_Rect startButtonRect = {100, 250, 600, 100};
    SDL_Rect quitButtonRect = {100, 450, 600, 100};

    SDL_RenderCopy(renderer, title, NULL, &titleRect);
    SDL_RenderCopy(renderer, startButton, NULL, &startButtonRect);
    SDL_RenderCopy(renderer, quitButton, NULL, &quitButtonRect);
}

/**
 * @brief Getter pour savoir si le jeu a démarré
 */
bool Menu::GetGameStarted() const {
    return gameStarted;
}

/**
 * @brief Getter pour savoir si le jeu doit quitter
 */
bool Menu::GetQuitGame() const {
    return quitGame;
}

/**
 * @brief Setter pour changer l'état booléen quand le jeu doit quitter
 * @param _quitGame
 */
void Menu::SetQuitGame(bool _quitGame) {
    quitGame = _quitGame;
}

/**
 * @brief Setter pour changer l'état booléen quand le jeu a démarré
 * @param _gameStarted
 */
void Menu::SetGameStarted(bool _gameStarted) {
    gameStarted = _gameStarted;
}

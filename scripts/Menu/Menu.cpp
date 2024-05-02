//
// Created by Logan on 02/05/2024.
//

#include "Menu.hpp"
Menu::Menu(SDL_Renderer* renderer, bool _gameStarted, bool _quitGame) : gameStarted(_gameStarted), quitGame(_quitGame){
    // Load the images for the title, start button, and quit button
    title = IMG_LoadTexture(renderer, "../resources/title.png");
    startButton = IMG_LoadTexture(renderer, "../resources/start_button.png");
    quitButton = IMG_LoadTexture(renderer, "../resources/quit_button.png");
}

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

bool Menu::GetGameStarted() const {
    return gameStarted;
}

bool Menu::GetQuitGame() const {
    return quitGame;
}

void Menu::SetQuitGame(bool _quitGame) {
    quitGame = _quitGame;
}

void Menu::SetGameStarted(bool _gameStarted) {
    gameStarted = _gameStarted;
}

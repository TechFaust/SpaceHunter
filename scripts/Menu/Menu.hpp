//
// Created by Logan on 02/05/2024.
//

#ifndef SPACEHUNTER_MENU_HPP
#define SPACEHUNTER_MENU_HPP

#include <SDL.h>
#include <SDL_image.h>

class Menu {
private:
    SDL_Texture* title;
    SDL_Texture* startButton;
    SDL_Texture* quitButton;

    bool gameStarted;
    bool quitGame;

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

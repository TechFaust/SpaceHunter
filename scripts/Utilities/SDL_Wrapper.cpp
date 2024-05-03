//
// Created by Groupe_2_Space_Hunter on 02/05/2024.
//

#include "SDL_Wrapper.hpp"

/**
 * @brief Constructeur de la classe SDL_Wrapper
 * @param width Taille de la fenêtre, en pixels
 * @param height Taille de la fenêtre, en pixels
 * @param name Nom de la fenêtre
 */
SDL_Wrapper::SDL_Wrapper(const int width, const int height, const std::string &name) :
        _width(width), _heigth(height) {
    _window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    _renderer = SDL_CreateRenderer(_window, -1, 0);
}

/**
 * @brief Destructeur de la classe SDL_Wrapper
 */
SDL_Wrapper::~SDL_Wrapper() {
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
}

/**
 * @brief Met la fenêtre en plein écran (WORK IN PROGRESS)
 */
void SDL_Wrapper::SetFullscreen() {
    SDL_SetWindowFullscreen(_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_GetWindowSize(_window, &_width, &_heigth);
}

/**
 * @brief Met la fenêtre en mode fenêtré (WORK IN PROGRESS)
 * @param height Taille de la fenêtre, en pixels
 * @param width Taille de la fenêtre, en pixels
 */
void SDL_Wrapper::SetWindowed(const int height, const int width) {
    SDL_SetWindowFullscreen(_window, 0);
    SDL_SetWindowSize(_window, width, height);
    _width = width;
    _heigth = height;
}

/**
 * @brief Getter du renderer (Moteur Graphique)
 * @return Le renderer (Moteur Graphique)
 */
SDL_Renderer* SDL_Wrapper::getRenderer() const {
    return _renderer;
}

/**
 * @brief Getter de la hauteur de la fenêtre
 * @return La hauteur de la fenêtre
 */
int SDL_Wrapper::getHeigth() const {
    return _heigth;
}
/**
 * @brief Getter de la largeur de la fenêtre
 * @return La largeur de la fenêtre
 */
int SDL_Wrapper::getWidth() const {
    return _width;
}
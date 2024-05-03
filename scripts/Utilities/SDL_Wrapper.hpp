//
// Created by Groupe_2_Space_Hunter on 02/05/2024.
//

#ifndef SPACEHUNTER_SDL_WRAPPER_HPP
#define SPACEHUNTER_SDL_WRAPPER_HPP


#include <SDL.h>
#include <string>

/**
 * @breif Classe qui gère l'initiation de la SDL, la création de la fenêtre et du renderer
 */
class SDL_Wrapper {
    SDL_Window *_window; // Fenêtre de l'application
    SDL_Renderer *_renderer; // Moteur graphique

    int _width, _heigth; // Taille de la fenêtre, en pixels

public:
    SDL_Wrapper(int width, int height, const std::string &name);
    ~SDL_Wrapper();

    void SetFullscreen();
    void SetWindowed(int height, int width);

    [[nodiscard]] SDL_Renderer* getRenderer() const;
    [[nodiscard]] int getWidth() const;
    [[nodiscard]] int getHeigth() const;
};

#endif //SPACEHUNTER_SDL_WRAPPER_HPP

//
// Created by Groupe_2_Space_Hunter on 01/05/2024.
//

#ifndef SPACEHUNTER_BACKGROUND_HPP
#define SPACEHUNTER_BACKGROUND_HPP

#include <SDL.h>
#include "SDL_image.h"
#include <iostream>

/**
 * @brief Classe qui gère l'arrière plan du jeu
 */
class Background {
private:
    SDL_Texture* background_texture; // Texture de l'arrière plan, ici notre PNG

public:

    /**
     * @brief Constructeur de l'arrière plan
     * @param renderer Moteur Graphique
     * @param background_path Chemin de l'image .png de l'arrière plan
     */
    Background(SDL_Renderer* renderer, const char* background_path){
        // Methode affichant l'arrière plan dans la fenetre de jeu.

        SDL_Surface* image = IMG_Load(background_path);

        background_texture = SDL_CreateTextureFromSurface(renderer,image);
        SDL_FreeSurface(image);

        SDL_RenderCopy(renderer, background_texture, nullptr, nullptr);
    }
//
    ~Background(){
        SDL_DestroyTexture(background_texture);
    }

    void RedrawBackground(SDL_Renderer* renderer);

};


#endif //SPACEHUNTER_BACKGROUND_HPP

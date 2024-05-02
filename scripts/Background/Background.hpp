//
// Created by Logan on 01/05/2024.
//

#ifndef SPACEHUNTER_BACKGROUND_HPP
#define SPACEHUNTER_BACKGROUND_HPP

#include <SDL.h>
#include "SDL_image.h"
#include <iostream>

class Background {
private:
    SDL_Texture* background_texture;

public:

    Background(SDL_Renderer* renderer, const char* background_path){

        SDL_Surface* image = IMG_Load(background_path);

        background_texture = SDL_CreateTextureFromSurface(renderer,image);
        SDL_FreeSurface(image);

        SDL_RenderCopy(renderer, background_texture, nullptr, nullptr);
    }

    ~Background(){
        SDL_DestroyTexture(background_texture);
    }

    void RedrawBackground(SDL_Renderer* renderer);

};


#endif //SPACEHUNTER_BACKGROUND_HPP

//
// Created by Logan on 30/04/2024.
//

#ifndef SPACEHUNTER_CHARACTER_HPP
#define SPACEHUNTER_CHARACTER_HPP
#include <SDL.h>
#include "SDL_image.h"
#include <iostream>
#include <vector>

class Character {
private:
    int health;
    int damage;
    int shield;

    int current_frame;

    std::vector<SDL_Texture*> texture;

    SDL_Rect position{};

public:
    Character(int _health, int _damage, int _shield, SDL_Renderer* renderer, std::string image) : health(_health), damage(_damage), shield(_shield), current_frame(0){

        for (int i = 1; i < 5; ++i) {
            std::string filename = "../resources/" + image + "_0" + std::to_string(i) + ".png";

            SDL_Surface* image = IMG_Load(filename.c_str());
            if(!image)
            {
                printf("Erreur de chargement de l'image : %s",SDL_GetError());
            }
            texture.push_back(SDL_CreateTextureFromSurface(renderer,image));
            SDL_FreeSurface(image);
        }

        position.x = 100;
        position.y = 100;
        position.h = 50;
        position.w = 50;


    }
    void Render(SDL_Renderer* renderer);
    void Animate();
    void SetNewPositionX(int _delta);
    void SetNewPositionY(int _delta);

};


#endif //SPACEHUNTER_CHARACTER_HPP

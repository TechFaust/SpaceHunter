//
// Created by Logan on 01/05/2024.
//

#ifndef SPACEHUNTER_BULLET_HPP
#define SPACEHUNTER_BULLET_HPP


#include <SDL.h>
#include "SDL_image.h"
#include <iostream>
#include <vector>
class Bullet {
private:
    int damage;
    int speed;

    int current_frame = 0;

    SDL_Rect position;

    std::vector<SDL_Texture*> texture;

public:

    Bullet(int _damage, int _speed, int _x, int _y, SDL_Renderer* renderer, const std::string& image_ref) :
    damage(_damage), speed(_speed), position({_x, _y, 10, 10}), current_frame(0){

        for (int i = 1; i < 5; ++i) {
            std::string filename = "../resources/" + image_ref + "_0" + std::to_string(i) + ".png";

            SDL_Surface* image = IMG_Load(filename.c_str());
            texture.push_back(SDL_CreateTextureFromSurface(renderer,image));
            SDL_FreeSurface(image);
        }

    }

    void Move();
    void Animate();
    void Render(SDL_Renderer* renderer);

    int GetDamage();

    SDL_Rect GetPosition();
};


#endif //SPACEHUNTER_BULLET_HPP

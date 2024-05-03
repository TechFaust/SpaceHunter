//
// Created by Logan on 02/05/2024.
//

#ifndef SPACEHUNTER_SHIP_HPP
#define SPACEHUNTER_SHIP_HPP


#include "Enemy.hpp"

class Ship : public Enemy{
private:

public:

    Ship(int _health, int _damage, int _delay,SDL_Renderer* renderer, const char* image_path) :
    Enemy(_health,_damage,_delay,renderer,image_path){};

void Move_Enemy() override;
void Shoot_Enemy(SDL_Renderer *renderer) override;
};


#endif //SPACEHUNTER_SHIP_HPP

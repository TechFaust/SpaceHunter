//
// Created by Logan on 03/05/2024.
//

#ifndef SPACEHUNTER_METEOR_HPP
#define SPACEHUNTER_METEOR_HPP

#include "Enemy.hpp"

class Meteor : public Enemy{
public:
    Meteor(int _health, int _damage, int _delay,SDL_Renderer* renderer, const char* image_path) :
    Enemy(_health,_damage,_delay,renderer,image_path){};

    void Move_Enemy() override;
    void Shoot_Enemy(SDL_Renderer *renderer) override;

};


#endif //SPACEHUNTER_METEOR_HPP

//
// Created by Logan on 02/05/2024.
//

#ifndef SPACEHUNTER_DOOMSHIP_HPP
#define SPACEHUNTER_DOOMSHIP_HPP


#include "Enemy.hpp"

class DoomShip : public Enemy{
private:
public:

    DoomShip(int _health, int _damage, int _shield, int _delay,SDL_Renderer* renderer, const char* image_path) :
    Enemy(_health,_damage,_shield,_delay,renderer,image_path){};

    void Move_Enemy() override;
    void Shoot_Enemy(SDL_Renderer *renderer) override;

};


#endif //SPACEHUNTER_DOOMSHIP_HPP

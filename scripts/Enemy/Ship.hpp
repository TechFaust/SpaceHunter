//
// Created by Groupe_2_Space_Hunter on 02/05/2024.
//

#ifndef SPACEHUNTER_SHIP_HPP
#define SPACEHUNTER_SHIP_HPP


#include "Enemy.hpp"
/**
 * @brief Declaration de l'ennemi "Ship", vaisseau ennemi
 */
class Ship : public Enemy{
private:

public:
/**
 * @brief Constructeur de Ship
 * @param _health Vie de l'ennemi
 * @param _damage Dégats de l'ennemi
 * @param _delay Délai de l'ennemi
 * @param image_path Reference de l'image de l'ennemi
 */
    Ship(int _health, int _damage, int _delay,SDL_Renderer* renderer, const char* image_path) :
    Enemy(_health,_damage,_delay,renderer,image_path){};

void Move_Enemy() override;
void Shoot_Enemy(SDL_Renderer *renderer) override;
};


#endif //SPACEHUNTER_SHIP_HPP

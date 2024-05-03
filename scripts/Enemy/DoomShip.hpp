//
// Created by Groupe_2_Space_Hunter on 02/05/2024.
//

#ifndef SPACEHUNTER_DOOMSHIP_HPP
#define SPACEHUNTER_DOOMSHIP_HPP


#include "Enemy.hpp"

/**
 * @brief Declaration de l'ennemi "Doomship", gros navire ennemi
 */

class DoomShip : public Enemy{
private:
public:

    /**
     * @brief Constructeur de DoomShip
     * @param _health Vie de l'ennemi
     * @param _damage Dégats de l'ennemi
     * @param _delay Délai entre chaque tir
     * @param renderer Moteur graphique pour afficher l'ennemi
     * @param image_path Reference de l'image de l'ennemi
     */
    DoomShip(int _health, int _damage, int _delay,SDL_Renderer* renderer, const char* image_path) :
    Enemy(_health,_damage,_delay,renderer,image_path){};

    void Move_Enemy() override;
    void Shoot_Enemy(SDL_Renderer *renderer) override;

};


#endif //SPACEHUNTER_DOOMSHIP_HPP

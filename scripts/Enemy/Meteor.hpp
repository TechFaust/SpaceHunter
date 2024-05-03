//
// Created by Groupe_2_Space_Hunter on 03/05/2024.
//

#ifndef SPACEHUNTER_METEOR_HPP
#define SPACEHUNTER_METEOR_HPP

#include "Enemy.hpp"

/**
 * @brief Declaration de la Classe Meteor et de sa methode propre: Meteor et celles hériter grace à Enemy
 */
class Meteor : public Enemy{
public:

    /**
     * @brief Constructeur de Meteor
     * @param _health Vie de l'ennemi
     * @param _damage Dégats de l'ennemi
     * @param _delay Délai entre chaque tir
     * @param renderer Moteur graphique pour afficher l'ennemi
     * @param image_path Reference de l'image de l'ennemi
     */
    Meteor(int _health, int _damage, int _delay,SDL_Renderer* renderer, const char* image_path) :
    Enemy(_health,_damage,_delay,renderer,image_path){};

    void Move_Enemy() override;
    void Shoot_Enemy(SDL_Renderer *renderer) override;

};


#endif //SPACEHUNTER_METEOR_HPP

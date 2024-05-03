//
// Created by Groupe_2_Space_Hunter on 03/05/2024.
//

#include "Meteor.hpp"

/**
 * @brief Definition des methodes de la classe "Meteor" qui herite de la classe Enemy.
 */
void Meteor::Move_Enemy() {

        SetNewPositionY(30);
        switch (rand() % 2) {
            case 0:
                SetNewPositionX(10);
                break;
            case 1:
                SetNewPositionX(-10);
                break;

    }
}
/**
 * @brief Definition du comportement de tir de l'ennemi "Meteor". Ici on s'attend à ce que le Meteor ne tire pas.
 * @param renderer Moteur Graphique pour afficher les tirs
 */
void Meteor::Shoot_Enemy(SDL_Renderer *renderer) {

}

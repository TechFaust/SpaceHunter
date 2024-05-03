//
// Created by Groupe_2_Space_Hunter on 02/05/2024.
//

#include "Ship.hpp"

/**
 * @brief Definition du comportements/mouvements de l'ennemi "Ship"
 */

void Ship::Move_Enemy() {
    SetNewPositionY(5);
    switch (rand() % 2) {
        case 0:
            SetNewPositionX(15);
            break;
        case 1:
            SetNewPositionX(-15);
            break;
    }
}

/**
* @brief Definition du comportements/tirs de l'ennemi "Ship"
* @param renderer Moteur graphique pour afficher les tirs.
*/

void Ship::Shoot_Enemy(SDL_Renderer *renderer) {
    if(GetDelay() < 0){
        GetBullets_Enemy().emplace_back(5,-10,GetPosition().x+20,GetPosition().y-5,renderer,"Laser_Orange");
        SetDelay(25);
    }
}

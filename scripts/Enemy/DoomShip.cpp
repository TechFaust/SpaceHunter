//
// Created by Groupe_2_Space_Hunter on 02/05/2024.
//

#include "DoomShip.hpp"

/**
 * @brief Definition du comportements des mouvements de l'ennemi "Ship"
 */
void DoomShip::Move_Enemy() {

    SetNewPositionY(5);
    switch (rand() % 2) {
        case 0:
            SetNewPositionX(5);
            break;
        case 1:
            SetNewPositionX(-5);
            break;
    }
}

/**
 * @brief Definition du comportements de tirs de l'ennemi "Ship"
 * @param renderer Moteur graphique pour afficher les tirs
 */
void DoomShip::Shoot_Enemy(SDL_Renderer *renderer) {

    if(GetDelay() < 0){
        GetBullets_Enemy().emplace_back(5,-10,GetPosition().x,GetPosition().y-5,renderer,"Laser_Rose");
        GetBullets_Enemy().emplace_back(5,-10,GetPosition().x+20 ,GetPosition().y-5,renderer,"Laser_Rose");
        SetDelay(35);
    }
}

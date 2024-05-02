//
// Created by Logan on 02/05/2024.
//

#include "Enemy.hpp"


void Enemy::Move_Enemy() {
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

void Enemy::Shoot_Enemy(SDL_Renderer *renderer) {
    bullets_enemy.emplace_back(5,-10,GetPosition().x+20,GetPosition().y-5,renderer,"Laser");
}

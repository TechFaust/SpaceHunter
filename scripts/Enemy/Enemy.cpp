//
// Created by Logan on 02/05/2024.
//

#include "Enemy.hpp"


void Enemy::Move_Enemy() {
    SetNewPositionY(30);
    switch (rand() % 2) {
        case 0:
            SetNewPositionX(5);
            break;
        case 1:
            SetNewPositionX(-5);
            break;
    }
}

void Enemy::Shoot_Enemy(SDL_Renderer *renderer) {}

std::vector<Bullet> &Enemy::GetBullets_Enemy() {
    return bullets_enemy;
}

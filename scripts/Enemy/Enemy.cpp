//
// Created by Logan on 02/05/2024.
//

#include "Enemy.hpp"



std::vector<Bullet> &Enemy::GetBullets_Enemy() {
    return bullets_enemy;
}

void Enemy::IsAttacked(int _damage) {
    SetHealth(GetHealth() - _damage);
}

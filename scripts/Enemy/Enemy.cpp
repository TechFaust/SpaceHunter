//
// Created by Groupe_2_Space_Hunter on 02/05/2024.
//

#include "Enemy.hpp"


/**
 * @brief Retourne les balles tirées par l'ennemi
 * @return std::vector<Bullet> & : Les balles tirées par l'ennemi
 */
std::vector<Bullet> &Enemy::GetBullets_Enemy() {
    return bullets_enemy;
}
/**
 * @brief L'ennemie se prend des dégats
 * @param _damage Dégats infligés
 */
void Enemy::IsAttacked(int _damage) {
    SetHealth(GetHealth() - _damage);
    if(GetHealth() <= 0){
        SetState(DEAD);
    }
}

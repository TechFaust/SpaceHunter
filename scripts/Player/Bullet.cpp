//
// Created by Groupe_2_Space_Hunter on 01/05/2024.
//

#include "Bullet.hpp"

/**
 * @brief Déplace le projectile
 */
void Bullet::Move() {
    position.y -= speed;
}

/**
 * @brief Affiche le projectile
 * @param renderer Moteur Graphique
 */
void Bullet::Render(SDL_Renderer* renderer){
    SDL_RenderCopy(renderer,texture[current_frame], nullptr, &position);
}

/**
 * @brief Récupère la position du projectile
 * @return la position du projectile
 */
SDL_Rect Bullet::GetPosition() {
    return position;
}

/**
 * @brief Anime le projectile
 */
void Bullet::Animate() {
    current_frame = (current_frame + 1) % texture.size();
}

/**
 * @brief Récupère les dégâts du projectile
 * @return les dégâts du projectile
 */
int Bullet::GetDamage() const {
    return damage;
}

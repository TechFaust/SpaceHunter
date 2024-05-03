//
// Created by Groupe_2_Space_Hunter on 02/05/2024.
//

#ifndef SPACEHUNTER_ENEMY_HPP
#define SPACEHUNTER_ENEMY_HPP

#include "../Utilities/Character.hpp"
#include "../Player/Bullet.hpp"

/**
 * @brief Classe représentant un ennemi
 */
class Enemy : public Character{
private:
    std::vector<Bullet> bullets_enemy; // Les balles tirées par l'ennemi présent en jeu
public:

    /**
     * @brief Constructeur de la classe Enemy
     * @param _health Vie de l'ennemi
     * @param _damage Dégats infligés par l'ennemi
     * @param _delay Délay entre chaque tir de l'ennemi
     * @param renderer Moteur de rendu
     * @param image_path Reférence de l'image de l'ennemi
     */
    Enemy(int _health, int _damage, int _delay,SDL_Renderer* renderer, const char* image_path) :
    Character(_health,_damage,_delay,renderer,image_path){};

    virtual void Shoot_Enemy(SDL_Renderer *renderer) = 0; // Fonction permettant à l'ennemi de tirer, virtuelle pure
    virtual void Move_Enemy() = 0; // Fonction permettant à l'ennemi de se déplacer, virtuelle pure
    void IsAttacked(int _damage) override;
    std::vector<Bullet>& GetBullets_Enemy();

};


#endif //SPACEHUNTER_ENEMY_HPP

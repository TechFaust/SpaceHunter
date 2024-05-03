//
// Created by Logan on 02/05/2024.
//

#ifndef SPACEHUNTER_ENEMY_HPP
#define SPACEHUNTER_ENEMY_HPP


#include "../Utilities/Character.hpp"
#include "../Player/Bullet.hpp"
class Enemy : public Character{
private:
    std::vector<Bullet> bullets_enemy;
public:
    Enemy(int _health, int _damage, int _delay,SDL_Renderer* renderer, const char* image_path) :
    Character(_health,_damage,_delay,renderer,image_path){};

    virtual void Shoot_Enemy(SDL_Renderer *renderer) = 0;
    virtual void Move_Enemy() = 0;
    void IsAttacked(int _damage) override;
    std::vector<Bullet>& GetBullets_Enemy();

};


#endif //SPACEHUNTER_ENEMY_HPP

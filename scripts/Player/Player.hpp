//
// Created by Logan on 30/04/2024.
//

#ifndef SPACEHUNTER_PLAYER_HPP
#define SPACEHUNTER_PLAYER_HPP


#include "../Utilities/Character.hpp"
#include <SDL.h>
#include "SDL_image.h"
#include <iostream>
#include "Bullet.hpp"

class Player : public Character{
private:
    std::vector<Bullet> bullets;
    int score;
    bool upgrade = false;
public:
    Player(int _health, int _damage, int _shield, SDL_Renderer* renderer, const char* image_path) :
    Character(_health,_damage,_shield,renderer,image_path), score(0){}

    void Action(SDL_Event& event,SDL_Renderer* renderer);

    void Shoot(SDL_Renderer* renderer);
    std::vector<Bullet>& GetBullets();

    void Add_Score(int _score);
    int GetScore();
};


#endif //SPACEHUNTER_PLAYER_HPP

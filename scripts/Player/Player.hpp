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
#include <SDL_ttf.h>

class Player : public Character{
private:
    std::vector<Bullet> bullets;
    int score;
    bool upgrade = false;

    SDL_Rect healthBarBackground;
    SDL_Rect healthBar;

public:
    Player(int _health, int _damage, int _shield,int _delay, SDL_Renderer* renderer, const char* image_path) :
    Character(_health,_damage,_shield,_delay,renderer,image_path), score(0){
        // Initialize health bar background
        healthBarBackground.x = 0;
        healthBarBackground.y = 580;  // 10 pixels above the character
        healthBarBackground.w = 100;  // Full health
        healthBarBackground.h = 20;  // Height of the health bar

        // Initialize health bar
        healthBar = healthBarBackground;  // Same position and size as background
    }

    void Action(SDL_Event& event,SDL_Renderer* renderer);

    void Shoot(SDL_Renderer* renderer);
    std::vector<Bullet>& GetBullets();

    void Add_Score(int _score);
    int GetScore();

    void RenderHealthBar(SDL_Renderer* renderer);
    void RenderScore(SDL_Renderer* renderer, TTF_Font* font);

    void SetUpgrade(bool _upgrade);
    void SetScore(int _score);

};


#endif //SPACEHUNTER_PLAYER_HPP

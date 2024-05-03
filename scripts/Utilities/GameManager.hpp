//
// Created by Logan on 03/05/2024.
//

#ifndef SPACEHUNTER_GAMEMANAGER_HPP
#define SPACEHUNTER_GAMEMANAGER_HPP

#include <SDL.h>
#include <memory>
#include "../Player/Player.hpp"
#include "../Enemy/Enemy.hpp"


class GameManager {
public:
    bool check_collision(SDL_Rect a, SDL_Rect b);

    void checkPlayerEnemyCollision(Player& player, std::vector<std::unique_ptr<Enemy>>& enemies);
    void checkBulletEnemyCollision(Player& player, std::vector<std::unique_ptr<Enemy>>& enemies);
    void checkEnemyBulletPlayerCollision(Player& player, std::vector<std::unique_ptr<Enemy>>& enemies);

    void removeBulletsOutOfScreen(Player& player);
    void removeEnemiesOutOfScreen(std::vector<std::unique_ptr<Enemy>>& enemies);

};


#endif //SPACEHUNTER_GAMEMANAGER_HPP

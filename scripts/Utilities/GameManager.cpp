//
// Created by Logan on 03/05/2024.
//

#include "GameManager.hpp"

bool GameManager::check_collision(SDL_Rect a, SDL_Rect b) {
    // The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    // Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    // Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    // If any of the sides from A are outside of B
    if (bottomA <= topB) {
        return false;
    }

    if (topA >= bottomB) {
        return false;
    }

    if (rightA <= leftB) {
        return false;
    }

    if (leftA >= rightB) {
        return false;
    }

    // If none of the sides from A are outside B
    return true;
}

void GameManager::checkPlayerEnemyCollision(Player &player, std::vector<std::unique_ptr<Enemy>> &enemies) {
    for (auto enemy_it = enemies.begin(); enemy_it != enemies.end(); /* no increment here */) {
        if (check_collision(player.GetPosition(), (*enemy_it)->GetPosition())) {
            player.IsAttacked((*enemy_it)->GetDamage());
            enemy_it = enemies.erase(enemy_it);
            player.Add_Score(1);
        } else {
            ++enemy_it;
        }
    }
}

void GameManager::checkBulletEnemyCollision(Player &player, std::vector<std::unique_ptr<Enemy>> &enemies) {
    for (auto bullet_it = player.GetBullets().begin();
         bullet_it != player.GetBullets().end(); /* no increment here */) {
        for (auto enemy_it = enemies.begin(); enemy_it != enemies.end(); /* no increment here */) {
            if (check_collision(bullet_it->GetPosition(), (*enemy_it)->GetPosition())) {

                (*enemy_it)->IsAttacked(bullet_it->GetDamage());
                if ((*enemy_it)->GetState() == DEAD) {
                    enemy_it = enemies.erase(enemy_it);
                    player.Add_Score(5);
                }

                bullet_it = player.GetBullets().erase(bullet_it);
                player.Add_Score(2);

                break;
            } else {
                ++enemy_it;
            }
        }
        if (bullet_it != player.GetBullets().end()) {
            ++bullet_it;
        }
    }

}

void GameManager::checkEnemyBulletPlayerCollision(Player &player, std::vector<std::unique_ptr<Enemy>> &enemies) {
    for (auto& enemy : enemies) {
        for (auto it = (*enemy).GetBullets_Enemy().begin(); it != (*enemy).GetBullets_Enemy().end(); /* no increment here */) {
            if (it->GetPosition().y > 600) { // assuming 600 is the bottom of the screen
                it = (*enemy).GetBullets_Enemy().erase(it);
            } else if (check_collision(player.GetPosition(), it->GetPosition())) {
                player.IsAttacked(it->GetDamage());
                it = (*enemy).GetBullets_Enemy().erase(it);
            } else {
                ++it;
            }
        }
    }
}

void GameManager::removeBulletsOutOfScreen(Player &player) {
    for (auto it = player.GetBullets().begin(); it != player.GetBullets().end(); /* no increment here */) {
        if (it->GetPosition().y < 0) { // assuming 0 is the top of the screen
            it = player.GetBullets().erase(it);
        } else {
            ++it;
        }
    }
}

void GameManager::removeEnemiesOutOfScreen(std::vector<std::unique_ptr<Enemy>> &enemies) {
    for (auto it = enemies.begin(); it != enemies.end(); /* no increment here */) {
        if ((*it)->GetPosition().y >= 580) {
            it = enemies.erase(it);
        } else {
            ++it;
        }
    }
}



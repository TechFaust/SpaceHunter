//
// Created by Logan on 30/04/2024.
//

#include "Player.hpp"

void Player::Action(SDL_Event &event, SDL_Renderer* renderer){
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_UP:
                SetNewPositionY(-8);
                break;
            case SDLK_DOWN:
                SetNewPositionY(8);
                break;
            case SDLK_LEFT:
                SetNewPositionX(-8);
                break;
            case SDLK_RIGHT:
                SetNewPositionX(8);
                break;
            case SDLK_SPACE:
                Shoot(renderer);
                break;
            default:
                break;
        }
    }
}

void Player::Shoot(SDL_Renderer *renderer) {
    bullets.emplace_back(5,10,GetPosition().x+20,GetPosition().y-5,renderer,"Laser");
}

std::vector<Bullet>& Player::GetBullets() {
    return bullets;
}

void Player::Add_Score(int _score) {
    score += _score;
}

int Player::GetScore() {
    return score;
}



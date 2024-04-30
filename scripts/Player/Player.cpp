//
// Created by Logan on 30/04/2024.
//

#include "Player.hpp"

void Player::Action(SDL_Event &event) {
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
            default:
                break;
        }
    }
}

//
// Created by Logan on 30/04/2024.
//

#include "Character.hpp"

void Character::Render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer,this->texture[current_frame], nullptr, &this->position);
}

void Character::SetNewPositionX(int _delta) {
    this->position.x += _delta;
}

void Character::SetNewPositionY(int _delta) {
    this->position.y += _delta;
}

void Character::Animate() {
    this->current_frame = (current_frame + 1) % texture.size();
}

SDL_Rect Character::GetPosition() {
    return position;
}

void Character::IsAttacked(int _damage) {
    if(shield > 0){
        shield -= _damage;
        if(shield < 0){
            health += shield;
            shield = 0;
        }
    } else{
        health -= _damage;
    }

    if(health <= 0){
        state = DEAD;
    }
}

STATE Character::GetState() {
    return state;
}

//
// Created by Logan on 30/04/2024.
//

#include "Character.hpp"

void Character::Render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer,this->texture[current_frame], nullptr, &this->position);
}

void Character::SetNewPositionX(int _delta) {
    this->position.x += _delta;
    if (GetPosition().x < 100) {
        position.x = 100;
    } else if (GetPosition().x > 700) {
        position.x = 700;
    }
}

void Character::SetNewPositionY(int _delta) {
    this->position.y += _delta;
    if (GetPosition().y < 50) {
        position.y = 50;
    } else if (GetPosition().y > 580) {
        position.y = 580;
    }
}

void Character::Animate() {
    this->current_frame = (current_frame + 1) % texture.size();
}

SDL_Rect Character::GetPosition() {
    return position;
}

void Character::IsAttacked(int _damage) {

}

STATE Character::GetState() {
    return state;
}

int Character::GetDamage() const {
    return damage;
}

int Character::GetHealth() const {
    return health;
}

int Character::GetDelay() const {
    return delay;
}

void Character::SetDelay(int _delay) {
    delay = _delay;
}

void Character::ReduceDelay(int _delta) {
    delay -= _delta;
}

void Character::SetState(STATE _state) {
    state = _state;
}

void Character::SetHealth(int _health) {
    health = _health;
}

void Character::SetPosition(int _x, int _y) {
    position.x = _x;
    position.y = _y;
}



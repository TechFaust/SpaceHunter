//
// Created by Logan on 01/05/2024.
//

#include "Bullet.hpp"

void Bullet::Move() {
    position.y -= speed;
}

void Bullet::Render(SDL_Renderer* renderer){
    SDL_RenderCopy(renderer,texture[current_frame], nullptr, &position);
}

SDL_Rect Bullet::GetPosition() {
    return position;
}

void Bullet::Animate() {
    current_frame = (current_frame + 1) % texture.size();
}

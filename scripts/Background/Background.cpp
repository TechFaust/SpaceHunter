//
// Created by Logan on 01/05/2024.
//

#include "Background.hpp"

void Background::RedrawBackground(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, background_texture, nullptr, nullptr);
}

//
// Created by Groupe_2_Space_Hunter on 01/05/2024.
//

#include "Background.hpp"




/**
 * @brief Redessine l'arrière plan
 * @param renderer
 */

void Background::RedrawBackground(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, background_texture, nullptr, nullptr);
}

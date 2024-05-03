//
// Created by Groupe_2_Space_Hunter on 01/05/2024.
//

#ifndef SPACEHUNTER_BULLET_HPP
#define SPACEHUNTER_BULLET_HPP


#include <SDL.h>
#include "SDL_image.h"
#include <iostream>
#include <vector>

/**
 * @class Bullet
 * @brief Classe qui gère les projectiles du joueur
 */
class Bullet {
private:
    int damage; // Dégâts du projectile
    int speed; // Vitesse du projectile

    int current_frame = 0; // Frame actuelle du projectile

    SDL_Rect position; // Position du projectile

    std::vector<SDL_Texture*> texture; // Texture du projectile

public:

    /**
     * @brief Constructeur de la classe Bullet
     * @param _damage Dégats du projectile
     * @param _speed Vitesse du projectile
     * @param _x Position x du projectile
     * @param _y Position y du projectile
     * @param renderer Moteur graphique pour afficher le projectile
     * @param image_ref Reference de l'image du projectile
     */
    Bullet(int _damage, int _speed, int _x, int _y, SDL_Renderer* renderer, const std::string& image_ref) :
    damage(_damage), speed(_speed), position({_x, _y, 10, 10}), current_frame(0){

        for (int i = 1; i < 5; ++i) {
            std::string filename = "../resources/" + image_ref + "_0" + std::to_string(i) + ".png";

            SDL_Surface* image = IMG_Load(filename.c_str());
            texture.push_back(SDL_CreateTextureFromSurface(renderer,image));
            SDL_FreeSurface(image);
        }

    }

    void Move();
    void Animate();
    void Render(SDL_Renderer* renderer);

    [[nodiscard]] int GetDamage() const;

    SDL_Rect GetPosition();
};


#endif //SPACEHUNTER_BULLET_HPP

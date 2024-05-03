//
// Created by Groupe_2_Space_Hunter on 30/04/2024.
//

#ifndef SPACEHUNTER_CHARACTER_HPP
#define SPACEHUNTER_CHARACTER_HPP
#include <SDL.h>
#include "SDL_image.h"
#include <iostream>
#include <vector>
typedef enum {
    ALIVE, DEAD
}STATE;


/**
 * @brief Classe abstraite représentant un personnage du jeu
 */

class Character {
private:

    int health; // Points de vie du personnage
    int damage; // Dégâts de collision du personnage

    STATE state; // Etat VIVANT OU MORT du personnage
    int current_frame; // Frame actuelle de l'animation
    int delay; // Délai entre chaque frame tirs

    std::vector<SDL_Texture*> texture; // Texture du personnage pour son animation

    SDL_Rect position{}; // Position du personnage

public:

    Character(int _health, int _damage, int _delay, SDL_Renderer* renderer, const std::string& image_ref);
    void Render(SDL_Renderer* renderer);
    void Animate();
    void SetNewPositionX(int _delta);
    void SetNewPositionY(int _delta);

    [[nodiscard]] int GetHealth() const;
    [[nodiscard]] int GetDamage() const;

    [[nodiscard]] int GetDelay() const;
    void SetDelay(int _delay);
    void ReduceDelay(int _delta);

    virtual void IsAttacked(int _damage) = 0;

    STATE GetState();
    void SetState(STATE _state);

    void SetHealth(int _health);

    SDL_Rect GetPosition();
    void SetPosition(int _x, int _y);

};


#endif //SPACEHUNTER_CHARACTER_HPP

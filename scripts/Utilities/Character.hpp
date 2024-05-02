//
// Created by Logan on 30/04/2024.
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

class Character {
private:
    int health;
    int damage;
    int shield;
    STATE state;
    int current_frame;
    int delay;

    std::vector<SDL_Texture*> texture;

    SDL_Rect position{};

public:
    Character(int _health, int _damage, int _shield, int _delay, SDL_Renderer* renderer, const std::string& image_ref) : health(_health), damage(_damage), shield(_shield), delay(_delay),current_frame(0){

        for (int i = 1; i < 5; ++i) {
            std::string filename = "../resources/" + image_ref + "_0" + std::to_string(i) + ".png";

            SDL_Surface* image = IMG_Load(filename.c_str());
            if(!image)
            {
                printf("Erreur de chargement de l'image : %s",SDL_GetError());
            }
            texture.push_back(SDL_CreateTextureFromSurface(renderer,image));
            SDL_FreeSurface(image);
        }

        if(image_ref == "PlayerSpaceship"){
            position.x = 350;
            position.y = 500;
        } else{
            position.x = rand() % 581 + 110; // rand() % (690 - 110 + 1) + 110
            position.y = 50;
        }
        position.h = 50;
        position.w = 50;

        state = ALIVE;

    }
    void Render(SDL_Renderer* renderer);
    void Animate();
    void SetNewPositionX(int _delta);
    void SetNewPositionY(int _delta);

    [[nodiscard]] int GetHealth() const;
    [[nodiscard]] int GetDamage() const;

    [[nodiscard]] int GetDelay() const;
    void SetDelay(int _delay);
    void ReduceDelay(int _delta);

    virtual void IsAttacked(int _damage);

    STATE GetState();
    void SetState(STATE _state);

    void SetHealth(int _health);

    SDL_Rect GetPosition();

};


#endif //SPACEHUNTER_CHARACTER_HPP

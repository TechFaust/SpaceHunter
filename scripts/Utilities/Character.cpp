//
// Created by Groupe_2_Space_Hunter on 30/04/2024.
//

#include "Character.hpp"

/**
 * @brief Fonction permettant d'afficher le personnage
 * @param renderer Moteur de rendu
 */
void Character::Render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer,this->texture[current_frame], nullptr, &this->position);
}

/**
 * @brief Fonction permettant de déplacer le personnage sur l'axe des abscisses en respectant les limitations
 * @param _delta Déplacements sur l'axe des abscisses
 */
void Character::SetNewPositionX(int _delta) {
    this->position.x += _delta;
    if (GetPosition().x < 100) {
        position.x = 100;
    } else if (GetPosition().x > 700) {
        position.x = 700;
    }
}

/**
 * @brief Fonction permettant de déplacer le personnage sur l'axe des ordonnées en respectant les limitations
 * @param _delta Déplacements sur l'axe des ordonnées
 */
void Character::SetNewPositionY(int _delta) {
    this->position.y += _delta;
    if (GetPosition().y < 50) {
        position.y = 50;
    } else if (GetPosition().y > 580) {
        position.y = 580;
    }
}

/**
 * @brief Fonction permettant de changer la frame actuelle de l'animation
 */
void Character::Animate() {
    this->current_frame = (current_frame + 1) % texture.size();
}

/**
 * @brief Fonction permettant de récupérer la position du personnage
 * @return Position du personnage
 */
SDL_Rect Character::GetPosition() {
    return position;
}

/**
 * @brief Fonction permettant de récupérer l'état du personnage
 * @return Etat du personnage
 */
STATE Character::GetState() {
    return state;
}

/**
 * @brief Fonction permettant de récupérer les dégâts de collision du personnage
 * @return Dégâts de collision du personnage
 */

int Character::GetDamage() const {
    return damage;
}

/**
 * @brief Fonction permettant de récupérer les points de vie du personnage
 * @return Points de vie du personnage
 */
int Character::GetHealth() const {
    return health;
}

/**
 * @brief Fonction permettant de récupérer le délai entre chaque tir
 * @return Le délais entre chaque tir
 */
int Character::GetDelay() const {
    return delay;
}

/**
 * @brief Fonction permettant de modifier le délai entre chaque tir
 * @param _delay Le nouveau délais
 */
void Character::SetDelay(int _delay) {
    delay = _delay;
}

/**
 * @brief Fonction permettant de réduire le délai (pour pouvoir tirer)
 * @param _delta Le délais à réduire
 */
void Character::ReduceDelay(int _delta) {
    delay -= _delta;
}

/**
 * @brief Fonction permettant de modifier l'état du personnage
 * @param _state Le nouvel état
 */
void Character::SetState(STATE _state) {
    state = _state;
}

/**
 * @brief Fonction permettant de modifier les points de vie du personnage
 * @param _health Les nouveaux points de vie
 */
void Character::SetHealth(int _health) {
    health = _health;
}

/**
 * @brief Fonction permettant de modifier la position du personnage
 * @param _x Nouvelle position en abscisse
 * @param _y Nouvelle position en ordonnée
 */
void Character::SetPosition(int _x, int _y) {
    position.x = _x;
    position.y = _y;
}

/**
 * @brief Constructeur de la classe Character
 * @param _health Vie du personnage
 * @param _damage Dégats de collision du personnage
 * @param _delay Délai entre chaque tir
 * @param renderer Moter de rendu
 * @param image_ref Reférence de l'image du personnage
 */
Character::Character(int _health, int _damage, int _delay, SDL_Renderer *renderer, const std::string &image_ref)  : health(_health), damage(_damage), delay(_delay),current_frame(0){

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



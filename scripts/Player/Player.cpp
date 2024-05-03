//
// Created by Groupe_2_Space_Hunter on 30/04/2024.
//

#include "Player.hpp"

/**
 * @brief Prise en charge des évènements joueur
 * @param event Evenements
 * @param renderer Moteur de rendu
 */
void Player::Action(SDL_Event &event, SDL_Renderer* renderer){
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
            case SDLK_SPACE:
                Shoot(renderer);
                break;
            default:
                break;
        }
    }
}

/**
 * @brief Tir du joueur
 * @param renderer
 */
void Player::Shoot(SDL_Renderer *renderer) {

   if(GetDelay() <= 0 && GetUpgrade()) {
       bullets.emplace_back(5, 10, GetPosition().x + 10, GetPosition().y - 5, renderer, "Laser");
       bullets.emplace_back(5, 10, GetPosition().x + 30, GetPosition().y - 5, renderer, "Laser");
       SetDelay(5);
   } else if(GetDelay() <= 0){
         bullets.emplace_back(5, 10, GetPosition().x + 20, GetPosition().y - 5, renderer, "Laser");
         SetDelay(5);
   }

   }

   /**
    * @brief Récupération des balles du joueur
    * @return Les balles du joueurs
    */

std::vector<Bullet>& Player::GetBullets() {
    return bullets;
}

/**
 * @brief Ajout de score
 * @param _score Score à ajouter
 */
void Player::Add_Score(int _score) {
    score += _score;
}

/**
 * @brief Récupération du score
 * @return Le score du joueur
 */
int Player::GetScore() const {
    return score;
}

/**
 * @brief Mise à jour de l'amélioration du joueur
 * @param _upgrade Booléen d'amélioration
 */
void Player::SetUpgrade(bool _upgrade) {
    upgrade = _upgrade;
}

/**
 * @brief Mise à jour du score en dur
 * @param _score Le score en dur
 */
void Player::SetScore(int _score) {
    score = _score;
}

/**
 * @brief Affichage de la barre de vie du joueur
 * @param renderer Mode de rendu
 */
void Player::RenderHealthBar(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // White color for background
    SDL_RenderFillRect(renderer, &healthBarBackground);
    healthBar.w = (GetHealth() / 100.0) * healthBarBackground.w;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Red color for health
    SDL_RenderFillRect(renderer, &healthBar);
}

/**
 * @brief Affichage du score du joueur
 * @param renderer Mode de rendu
 * @param font Police d'écriture
 */
void Player::RenderScore(SDL_Renderer *renderer, TTF_Font *font) {

    SDL_Rect scoreRect;
    scoreRect.x = 0;  //controls the rect's x coordinate
    scoreRect.y = 480; // controls the rect's y coordinte
    scoreRect.w = 100; // controls the width of the rect
    scoreRect.h = 50; // controls the height of the rect

    // Set the drawing color to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // Fill the rectangle with the current drawing color (black)
    SDL_RenderFillRect(renderer, &scoreRect);

    SDL_Color white = {255, 255, 255, 255}; // RGB color for white
    std::string scoreText = "Score: " + std::to_string(score);
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, scoreText.c_str(), white);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    SDL_Rect Message_rect; //create a rect
    Message_rect.x = 0;  //controls the rect's x coordinate
    Message_rect.y = 480; // controls the rect's y coordinte
    Message_rect.w = 100; // controls the width of the rect
    Message_rect.h = 50; // controls the height of the rect

    // Render the message to the screen
    SDL_RenderCopy(renderer, Message, nullptr, &Message_rect);

    // Free the resources
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);


}

/**
 * @brief Récupération de l'amélioration du joueur
 * @return Booléen d'amélioration
 */
bool Player::GetUpgrade() const {
    return upgrade;
}

/**
 * @brief Unlock du double tirs du joueur en fonction de son score
 */
void Player::Upgrade() {
    if(score >= 250){
        upgrade = true;
    }
}

/**
 * @brief Vérification quand le joueur est attaqué
 * @param _damage dégats infligés par l'ennemi
 */
void Player::IsAttacked(int _damage) {
    if(shield > 0){
        shield -= _damage;
        if(shield < 0){
            int temp_health = GetHealth();
            temp_health += shield;
            SetHealth(temp_health);
            shield = 0;
        }
    } else{
        int temp_health = GetHealth();
        temp_health -= _damage;
        SetHealth(temp_health);
    }

    if(GetHealth() <= 0){
        SetState(DEAD);
    }
}


